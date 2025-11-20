import subprocess
import random
import sys
import os

# --- CONFIGURATION ---
PUSH_SWAP_EXEC = "./push_swap"
# ---------------------

class Colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'

class StackSimulator:
    """
    Simulates the stack operations strictly according to 42 Subject rules.
    This acts as the 'Checker'.
    """
    def __init__(self, numbers):
        self.a = list(numbers) # Top of stack is index 0
        self.b = []

    def sa(self):
        if len(self.a) > 1:
            self.a[0], self.a[1] = self.a[1], self.a[0]

    def sb(self):
        if len(self.b) > 1:
            self.b[0], self.b[1] = self.b[1], self.b[0]

    def ss(self):
        self.sa()
        self.sb()

    def pa(self):
        if len(self.b) > 0:
            self.a.insert(0, self.b.pop(0))

    def pb(self):
        if len(self.a) > 0:
            self.b.insert(0, self.a.pop(0))

    def ra(self):
        if len(self.a) > 1:
            self.a.append(self.a.pop(0))

    def rb(self):
        if len(self.b) > 1:
            self.b.append(self.b.pop(0))

    def rr(self):
        self.ra()
        self.rb()

    def rra(self):
        if len(self.a) > 1:
            self.a.insert(0, self.a.pop())

    def rrb(self):
        if len(self.b) > 1:
            self.b.insert(0, self.b.pop())

    def rrr(self):
        self.rra()
        self.rrb()

    def execute(self, op):
        op = op.strip()
        if op == "sa": self.sa()
        elif op == "sb": self.sb()
        elif op == "ss": self.ss()
        elif op == "pa": self.pa()
        elif op == "pb": self.pb()
        elif op == "ra": self.ra()
        elif op == "rb": self.rb()
        elif op == "rr": self.rr()
        elif op == "rra": self.rra()
        elif op == "rrb": self.rrb()
        elif op == "rrr": self.rrr()
        else:
            return False # Invalid operation
        return True

    def is_sorted(self):
        # Stack B must be empty
        if len(self.b) != 0:
            return False, "Stack B is not empty"
        # Stack A must be sorted ascending
        if self.a != sorted(self.a):
            return False, "Stack A is not sorted"
        return True, "OK"

def run_test(stack_size):
    # 1. Generate Random Numbers
    numbers = random.sample(range(-10000, 10000), stack_size)
    str_nums = [str(n) for n in numbers]

    # 2. Run ./push_swap
    try:
        process = subprocess.Popen(
            [PUSH_SWAP_EXEC] + str_nums,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        stdout, stderr = process.communicate()
    except FileNotFoundError:
        print(f"{Colors.FAIL}Error: {PUSH_SWAP_EXEC} not found. Run 'make' first.{Colors.ENDC}")
        sys.exit(1)

    if stderr:
        print(f"{Colors.WARNING}Stderr Output: {stderr.strip()}{Colors.ENDC}")

    operations = stdout.strip().split('\n')
    # Handle case where no operations are printed (already sorted)
    if operations == ['']: operations = []

    # 3. Verify with Simulator
    sim = StackSimulator(numbers)
    for op in operations:
        if not op: continue
        valid = sim.execute(op)
        if not valid:
            return {
                "status": "FAIL",
                "msg": f"Invalid Instruction: '{op}'",
                "ops": 0,
                "nums": numbers
            }

    is_sorted, msg = sim.is_sorted()
    
    if is_sorted:
        return {"status": "OK", "ops": len(operations), "nums": numbers}
    else:
        return {"status": "FAIL", "msg": msg, "ops": len(operations), "nums": numbers, "final_a": sim.a[:10]}

def main():
    if len(sys.argv) < 2:
        print(f"Usage: python3 tester.py <stack_size> [num_tests]")
        print(f"Example: python3 tester.py 100 10")
        sys.exit(1)

    stack_size = int(sys.argv[1])
    num_tests = int(sys.argv[2]) if len(sys.argv) > 2 else 1

    print(f"{Colors.HEADER}Running {num_tests} tests with stack size {stack_size}...{Colors.ENDC}")
    print("-" * 60)

    results = []
    failures = 0

    for i in range(num_tests):
        res = run_test(stack_size)
        
        if res["status"] == "OK":
            results.append(res["ops"])
            print(f"Test {i+1}: {Colors.OKGREEN}OK{Colors.ENDC} ({res['ops']} instructions)")
        else:
            failures += 1
            print(f"Test {i+1}: {Colors.FAIL}FAIL{Colors.ENDC} -> {res['msg']}")
            print(f"   Input: {res['nums'][:10]}...")
            if 'final_a' in res:
                print(f"   Top of Stack A: {res['final_a']}...")

    print("-" * 60)
    if len(results) > 0:
        avg = sum(results) / len(results)
        print(f"Tests Passed: {len(results)}/{num_tests}")
        print(f"Min: {min(results)}")
        print(f"Max: {max(results)}")
        print(f"Avg: {int(avg)}")
        
        # Efficiency Grading (Approximation for 100 and 500)
        if stack_size == 100:
            if avg < 700: grade = f"{Colors.OKGREEN}5/5{Colors.ENDC}"
            elif avg < 900: grade = f"{Colors.OKGREEN}4/5{Colors.ENDC}"
            elif avg < 1100: grade = f"{Colors.WARNING}3/5{Colors.ENDC}"
            elif avg < 1300: grade = f"{Colors.WARNING}2/5{Colors.ENDC}"
            elif avg < 1500: grade = f"{Colors.FAIL}1/5{Colors.ENDC}"
            else: grade = f"{Colors.FAIL}0/5{Colors.ENDC}"
            print(f"Estimated Grade (Size 100): {grade}")
        elif stack_size == 500:
            if avg < 5500: grade = f"{Colors.OKGREEN}5/5{Colors.ENDC}"
            elif avg < 7000: grade = f"{Colors.OKGREEN}4/5{Colors.ENDC}"
            elif avg < 8500: grade = f"{Colors.WARNING}3/5{Colors.ENDC}"
            elif avg < 10000: grade = f"{Colors.WARNING}2/5{Colors.ENDC}"
            elif avg < 11500: grade = f"{Colors.FAIL}1/5{Colors.ENDC}"
            else: grade = f"{Colors.FAIL}0/5{Colors.ENDC}"
            print(f"Estimated Grade (Size 500): {grade}")

    else:
        print(f"{Colors.FAIL}All tests failed.{Colors.ENDC}")

if __name__ == "__main__":
    main()