#!/usr/bin/env python3
"""Utility script to stress-test the push_swap binary.

Features:
    * Generates random unique integer lists for stack a.
    * Executes ./push_swap (or a custom binary) for each list.
    * Simulates all operations to verify that the produced instructions are valid.
    * Optionally pipes the instructions to an external checker binary.
    * Prints per-test diagnostics and aggregates operation statistics.
"""

from __future__ import annotations

import argparse
import random
import statistics
import subprocess
import sys
import time
from dataclasses import dataclass
from pathlib import Path
from typing import List, Sequence


InstructionList = List[str]


@dataclass
class TestResult:
    index: int
    values: List[int]
    ops: InstructionList
    duration: float
    error: str | None = None
    checker_output: str | None = None

    @property
    def passed(self) -> bool:
        return self.error is None

    @property
    def op_count(self) -> int:
        return len(self.ops)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Randomized tester for the 42 push_swap project."
    )
    parser.add_argument(
        "-b",
        "--binary",
        default="./push_swap",
        help="path to the push_swap executable (default: ./push_swap)",
    )
    parser.add_argument(
        "-c",
        "--checker",
        help=(
            "optional path to the checker binary. When provided, instructions will "
            "also be validated via that checker"
        ),
    )
    parser.add_argument(
        "-n",
        "--tests",
        type=int,
        default=10,
        help="number of random test cases to run (default: 10)",
    )
    parser.add_argument(
        "-s",
        "--size",
        type=int,
        default=5,
        help="size of stack a (default: 5)",
    )
    parser.add_argument(
        "--min",
        dest="min_value",
        type=int,
        default=-1000,
        help="minimum random value (inclusive, default: -1000)",
    )
    parser.add_argument(
        "--max",
        dest="max_value",
        type=int,
        default=1000,
        help="maximum random value (inclusive, default: 1000)",
    )
    parser.add_argument(
        "--seed",
        type=int,
        help="seed for Python's random module (default: none, i.e. system randomness)",
    )
    parser.add_argument(
        "-v",
        "--verbose",
        action="store_true",
        help="print the generated stack and the operations for each test",
    )
    parser.add_argument(
        "--show-errors",
        action="store_true",
        help="print stderr emitted by push_swap when a failure occurs",
    )
    return parser.parse_args()


def ensure_inputs_valid(args: argparse.Namespace) -> None:
    if args.size <= 0:
        raise SystemExit("Stack size must be positive.")
    if args.min_value > args.max_value:
        raise SystemExit("Minimum value cannot exceed maximum value.")
    range_size = args.max_value - args.min_value + 1
    if range_size < args.size:
        raise SystemExit(
            f"Cannot pick {args.size} unique numbers in range "
            f"[{args.min_value}, {args.max_value}]."
        )
    binary_path = Path(args.binary)
    if not binary_path.exists():
        raise SystemExit(f"push_swap binary not found at: {binary_path}")
    if args.checker and not Path(args.checker).exists():
        raise SystemExit(f"checker binary not found at: {args.checker}")


def generate_case(size: int, min_value: int, max_value: int) -> List[int]:
    # random.sample guarantees unique values.
    return random.sample(range(min_value, max_value + 1), size)


def run_push_swap(binary: str, values: Sequence[int]) -> subprocess.CompletedProcess:
    cmd = [binary] + [str(v) for v in values]
    return subprocess.run(
        cmd,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        check=False,
    )


def execute_checker(
    checker: str, values: Sequence[int], instructions: str
) -> subprocess.CompletedProcess:
    cmd = [checker] + [str(v) for v in values]
    return subprocess.run(
        cmd,
        input=instructions,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        check=False,
    )


def apply_instructions(values: Sequence[int], ops: InstructionList) -> tuple[List[int], List[int]]:
    a = list(values)
    b: List[int] = []
    for op in ops:
        if op == "sa":
            if len(a) >= 2:
                a[0], a[1] = a[1], a[0]
        elif op == "sb":
            if len(b) >= 2:
                b[0], b[1] = b[1], b[0]
        elif op == "ss":
            if len(a) >= 2:
                a[0], a[1] = a[1], a[0]
            if len(b) >= 2:
                b[0], b[1] = b[1], b[0]
        elif op == "pa":
            if b:
                a.insert(0, b.pop(0))
        elif op == "pb":
            if a:
                b.insert(0, a.pop(0))
        elif op == "ra":
            if len(a) >= 2:
                a.append(a.pop(0))
        elif op == "rb":
            if len(b) >= 2:
                b.append(b.pop(0))
        elif op == "rr":
            if len(a) >= 2:
                a.append(a.pop(0))
            if len(b) >= 2:
                b.append(b.pop(0))
        elif op == "rra":
            if len(a) >= 2:
                a.insert(0, a.pop())
        elif op == "rrb":
            if len(b) >= 2:
                b.insert(0, b.pop())
        elif op == "rrr":
            if len(a) >= 2:
                a.insert(0, a.pop())
            if len(b) >= 2:
                b.insert(0, b.pop())
        else:
            raise ValueError(f"Unknown instruction '{op}'")
    return a, b


def is_sorted(stack: Sequence[int]) -> bool:
    return all(stack[i] < stack[i + 1] for i in range(len(stack) - 1))


def run_test_case(
    index: int, args: argparse.Namespace, values: List[int]
) -> TestResult:
    start = time.perf_counter()
    proc = run_push_swap(args.binary, values)
    duration = time.perf_counter() - start
    stdout = proc.stdout
    stderr = proc.stderr

    if proc.returncode != 0:
        return TestResult(
            index=index,
            values=values,
            ops=[],
            duration=duration,
            error=f"push_swap exited with code {proc.returncode}",
            checker_output=stderr.strip() if stderr else None,
        )

    if stderr and args.show_errors:
        print(f"[stderr case {index}] {stderr.strip()}", file=sys.stderr)

    instructions = [line.strip() for line in stdout.splitlines() if line.strip()]

    try:
        final_a, final_b = apply_instructions(values, instructions)
    except ValueError as err:
        return TestResult(
            index=index,
            values=values,
            ops=instructions,
            duration=duration,
            error=str(err),
        )

    if final_b:
        return TestResult(
            index=index,
            values=values,
            ops=instructions,
            duration=duration,
            error="Stack b is not empty after executing instructions.",
        )

    if not is_sorted(final_a):
        return TestResult(
            index=index,
            values=values,
            ops=instructions,
            duration=duration,
            error="Stack a is not sorted in ascending order.",
        )

    checker_output = None
    if args.checker:
        checker_proc = execute_checker(args.checker, values, stdout)
        checker_output = checker_proc.stdout.strip()
        if checker_proc.returncode != 0:
            return TestResult(
                index=index,
                values=values,
                ops=instructions,
                duration=duration,
                error=f"checker exited with code {checker_proc.returncode}",
                checker_output=checker_output or checker_proc.stderr.strip(),
            )
        if checker_output != "OK":
            return TestResult(
                index=index,
                values=values,
                ops=instructions,
                duration=duration,
                error=f"checker returned '{checker_output}'",
            )

    return TestResult(
        index=index,
        values=values,
        ops=instructions,
        duration=duration,
        checker_output=checker_output,
    )


def summarize_results(results: Sequence[TestResult]) -> None:
    passed = [r for r in results if r.passed]
    failed = [r for r in results if not r.passed]
    total = len(results)

    if passed:
        counts = [r.op_count for r in passed]
        avg_ops = statistics.mean(counts)
        median_ops = statistics.median(counts)
        best = min(counts)
        worst = max(counts)
        print("\nOperation statistics for successful runs:")
        print(f"  Cases: {len(passed)} / {total}")
        print(f"  Avg / Median: {avg_ops:.2f} / {median_ops:.2f}")
        print(f"  Best / Worst: {best} / {worst}")
    else:
        print("\nNo successful test cases.")

    if failed:
        print(f"\nFailures ({len(failed)} cases):")
        for result in failed:
            value_preview = " ".join(map(str, result.values))
            print(f"  Case #{result.index}: {result.error}")
            print(f"    Input: {value_preview}")
            if result.ops:
                print(f"    Ops produced: {result.op_count}")
            if result.checker_output:
                print(f"    Checker output: {result.checker_output}")
    else:
        print("\nAll cases passed ✅")


def main() -> None:
    args = parse_args()
    ensure_inputs_valid(args)
    if args.seed is not None:
        random.seed(args.seed)

    print(
        f"Running {args.tests} test(s) | size={args.size} | "
        f"range=[{args.min_value},{args.max_value}] | binary={args.binary}"
    )
    if args.checker:
        print(f"Using checker: {args.checker}")

    results: List[TestResult] = []
    for idx in range(1, args.tests + 1):
        values = generate_case(args.size, args.min_value, args.max_value)
        result = run_test_case(idx, args, values)
        results.append(result)
        status = "PASS" if result.passed else "FAIL"
        line = f"[{idx:03}] {status} | ops={result.op_count:4d} | time={result.duration*1000:6.2f} ms"
        print(line)
        if args.verbose:
            numbers = " ".join(map(str, values))
            print(f"    input: {numbers}")
            if result.ops:
                print(f"    ops: {' '.join(result.ops)}")
        if not result.passed and not args.verbose:
            numbers = " ".join(map(str, values))
            print(f"    reason: {result.error}")
            print(f"    input: {numbers}")
            if args.checker and result.checker_output:
                print(f"    checker: {result.checker_output}")

    summarize_results(results)


if __name__ == "__main__":
    main()
