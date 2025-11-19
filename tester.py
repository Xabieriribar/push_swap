import subprocess
import random
import sys
import os

# --- CONFIGURATION ---
PUSH_SWAP_EXEC = "./push_swap"
NUM_TESTS = 5          # How many times to run each test case
TEST_SIZES = [3, 5, 100, 500] # Stack sizes to test
# ---------------------

class Colors:
    GREEN = '\033[92m'
    RED = '\033[91m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    RESET = '\033[0m'

def get_random_numbers(count):
    """Generates a list of 'count' unique random integers."""
    range_limit = count * 10
    return random.sample(range(-range_limit, range_limit), count)

def run_push_swap(numbers):
    """Runs push_swap with the given numbers and returns the list of instructions."""
    args = [PUSH_SWAP_EXEC] + [str(n) for n in numbers]
    try:
        result = subprocess.run(args, capture_output=True, text=True, check=True)
        output = result.stdout.strip()
        if not output:
            return []
        return output.split('\n')
    except subprocess.CalledProcessError as e:
        print(f"{Colors.RED}Error running push_swap: {e}{Colors.RESET}")
        return None
    except FileNotFoundError:
        print(f"{Colors.RED}Executable '{PUSH_SWAP_EXEC}' not found!{Colors.RESET}")
        sys.exit(1)

def simulate_operations(stack_a, instructions):
    """
    Simulates the stack operations to verify correctness.
    Returns (final_stack_a, final_stack_b, valid_flag)
    """
    stack_b = []
    
    ops = {
        'sa': lambda a, b: (a.insert(0, a.pop(1)) if len(a) > 1 else None),
        'sb': lambda a, b: (b.insert(0, b.pop(1)) if len(b) > 1 else None),
        'ss': lambda a, b: (ops['sa'](a, b), ops['sb'](a, b)),
        'pa': lambda a, b: a.insert(0, b.pop(0)) if b else None,
        'pb': lambda a, b: b.insert(0, a.pop(0)) if a else None,
        'ra': lambda a, b: a.append(a.pop(0)) if len(a) > 1 else None,
        'rb': lambda a, b: b.append(b.pop(0)) if len(b) > 1 else None,
        'rr': lambda a, b: (ops['ra'](a, b), ops['rb'](a, b)),
        'rra': lambda a, b: a.insert(0, a.pop()) if len(a) > 1 else None,
        'rrb': lambda a, b: b.insert(0, b.pop()) if len(b) > 1 else None,
        'rrr': lambda a, b: (ops['rra'](a, b), ops['rrb'](a, b)),
    }

    for instr in instructions:
        instr = instr.strip()
        if not instr: continue
        if instr not in ops:
            print(f"{Colors.RED}Unknown instruction: {instr}{Colors.RESET}")
            return stack_a, stack_b, False
        ops[instr](stack_a, stack_b)
        
    return stack_a, stack_b, True

def check_limits(size, count):
    """Checks if the operation count meets the 42 subject requirements."""
    limit = None
    if size == 3 and count > 3: return False, 3
    if size == 5 and count > 12: return False, 12
    if size == 100: limit = 700
    if size == 500: limit = 5500
    
    if limit and count > limit:
        return False, limit
    return True, limit

def main():
    print(f"{Colors.BLUE}=== PUSH_SWAP PYTHON TESTER ==={Colors.RESET}\n")
    
    if not os.path.exists(PUSH_SWAP_EXEC):
        print(f"{Colors.RED}FAIL: {PUSH_SWAP_EXEC} not found. Compile your project first.{Colors.RESET}")
        return

    total_errors = 0

    for size in TEST_SIZES:
        print(f"{Colors.YELLOW}Testing Stack Size: {size}{Colors.RESET}")
        moves_history = []
        
        for i in range(NUM_TESTS):
            nums = get_random_numbers(size)
            # Create a copy for simulation because lists are mutable
            nums_copy = list(nums) 
            
            instructions = run_push_swap(nums)
            
            if instructions is None:
                continue
                
            count = len(instructions)
            moves_history.append(count)
            
            # Verify Sorting
            res_a, res_b, valid_ops = simulate_operations(nums_copy, instructions)
            
            is_sorted = (res_a == sorted(nums)) and (len(res_b) == 0)
            passed_limit, limit = check_limits(size, count)

            # Output status
            if is_sorted and passed_limit and valid_ops:
                status = f"{Colors.GREEN}[OK]{Colors.RESET}"
            else:
                status = f"{Colors.RED}[FAIL]{Colors.RESET}"
                total_errors += 1
                if not is_sorted: print(f"  -> Not sorted or Stack B not empty.")
                if not valid_ops: print(f"  -> Invalid instruction detected.")
                if not passed_limit: print(f"  -> Over limit! ({count} > {limit})")

            # Optional: Print individual test results (can be verbose)
            # print(f"  Test {i+1}: {status} ({count} ops)")

        # Summary for this size
        avg = sum(moves_history) // len(moves_history) if moves_history else 0
        max_ops = max(moves_history) if moves_history else 0
        print(f"  Average Ops: {Colors.BLUE}{avg}{Colors.RESET} | Max Ops: {Colors.BLUE}{max_ops}{Colors.RESET}")
        
        # Check against strict 42 benchmarks for 100/500
        if size == 100:
            if max_ops < 700: print(f"  Rating: {Colors.GREEN}5/5 (Excellent){Colors.RESET}")
            elif max_ops < 900: print(f"  Rating: {Colors.YELLOW}4/5{Colors.RESET}")
            else: print(f"  Rating: {Colors.RED}FAIL{Colors.RESET}")
        elif size == 500:
            if max_ops < 5500: print(f"  Rating: {Colors.GREEN}5/5 (Excellent){Colors.RESET}")
            elif max_ops < 7000: print(f"  Rating: {Colors.YELLOW}4/5{Colors.RESET}")
            else: print(f"  Rating: {Colors.RED}FAIL{Colors.RESET}")
        print("-" * 40)

    if total_errors == 0:
        print(f"\n{Colors.GREEN}ALL TESTS PASSED! Great job.{Colors.RESET}")
    else:
        print(f"\n{Colors.RED}SOME TESTS FAILED. Check output above.{Colors.RESET}")

if __name__ == "__main__":
    main()