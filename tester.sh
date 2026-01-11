#!/bin/bash

# --- COLORS ---
GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
CYAN="\033[36m"
BLUE="\033[34m"
BOLD="\033[1m"
RESET="\033[0m"

# --- CONFIG ---
PUSH_SWAP="./push_swap"
CHECKER="./checker_OS" # Change to ./checker_linux if on Linux
ITERATIONS=20          # Number of tests for 100 and 500

printf "${BOLD}${CYAN}Push_swap Tester - Definitive Edition${RESET}\n\n"

# Check if push_swap exists
if [ ! -f "$PUSH_SWAP" ]; then
    printf "${RED}Error: $PUSH_SWAP not found. Run 'make' first.${RESET}\n"
    exit 1
fi

# Function to run a test
run_test() {
    local size=$1
    local limit=$2
    local total_ops=0
    local max_ops=0
    local min_ops=2147483647
    local failed=0

    printf "${BOLD}${BLUE}Testing $size numbers (Limit: $limit, Iterations: $ITERATIONS)${RESET}\n"

    for ((i=1; i<=ITERATIONS; i++)); do
        ARG=$(ruby -e "print (1..$size).to_a.shuffle.join(' ')")
        OPS=$($PUSH_SWAP $ARG | wc -l)
        
        # Check correctness if checker exists
        if [ -f "$CHECKER" ]; then
            RESULT=$($PUSH_SWAP $ARG | $CHECKER $ARG)
            if [ "$RESULT" != "OK" ]; then
                printf "  ${RED}Iteration $i: KO!${RESET}\n"
                failed=$((failed + 1))
            fi
        fi

        total_ops=$((total_ops + OPS))
        [ $OPS -gt $max_ops ] && max_ops=$OPS
        [ $OPS -lt $min_ops ] && min_ops=$OPS
    done

    local avg_ops=$((total_ops / ITERATIONS))

    # Color coding based on performance
    local color=$GREEN
    [ $avg_ops -gt $limit ] && color=$RED

    printf "  Avg: ${color}$avg_ops${RESET} | Max: $max_ops | Min: $min_ops"
    if [ $failed -eq 0 ]; then
        printf " | Correctness: ${GREEN}OK${RESET}\n"
    else
        printf " | Correctness: ${RED}$failed FAILED${RESET}\n"
    fi
    echo "-------------------------------------------------------"
}

# --- 1. IDENTITY TEST ---
printf "${BOLD}${YELLOW}1. Identity Test (Already Sorted)${RESET}\n"
RES=$($PUSH_SWAP 1 2 3 4 5)
if [ -z "$RES" ]; then
    printf "  ${GREEN}OK: No output for sorted list.${RESET}\n"
else
    printf "  ${RED}FAIL: Output detected for sorted list.${RESET}\n"
fi
echo "-------------------------------------------------------"

# --- 2. SIMPLE SORTS ---
run_test 3 3
run_test 5 12

# --- 3. MIDDLE SORTS (100) ---
run_test 100 700

# --- 4. ADVANCED SORTS (500) ---
run_test 500 5500

# --- 5. ERROR HANDLING ---
printf "${BOLD}${YELLOW}5. Error Handling${RESET}\n"

test_error() {
    local msg=$1
    local arg=$2
    printf "  %-30s : " "$msg"
    ERR=$($PUSH_SWAP $arg 2>&1 | tr -d '\n')
    if [ "$ERR" == "Error" ]; then
        printf "${GREEN}OK${RESET}\n"
    else
        printf "${RED}FAIL (Got: '$ERR')${RESET}\n"
    fi
}

test_error "Non-numeric" "1 2 a 4"
test_error "Duplicate" "1 2 2 4"
test_error "MAX_INT Overflow" "2147483648"
test_error "MIN_INT Underflow" "-2147483649"
test_error "Empty String Arg" "\"\""

printf "  %-30s : " "No Arguments (Silent)"
RES=$($PUSH_SWAP 2>&1)
if [ -z "$RES" ]; then
    printf "${GREEN}OK${RESET}\n"
else
    printf "${RED}FAIL (Got: '$RES')${RESET}\n"
fi

echo "-------------------------------------------------------"

# --- 6. MEMORY LEAKS (VALGRIND) ---
if command -v valgrind &> /dev/null; then
    printf "${BOLD}${YELLOW}6. Memory Leak Check (Valgrind)${RESET}\n"
    ARG=$(ruby -e "print (1..100).to_a.shuffle.join(' ')")
    valgrind --leak-check=full --show-leak-kinds=all $PUSH_SWAP $ARG > /dev/null 2> valgrind_log
    if grep -q "All heap blocks were freed -- no leaks are possible" valgrind_log; then
        printf "  ${GREEN}No leaks detected.${RESET}\n"
    else
        printf "  ${RED}Leaks detected! Check valgrind_log.${RESET}\n"
    fi
    rm valgrind_log
else
    printf "${CYAN}Valgrind not found, skipping leak check.${RESET}\n"
fi

printf "\n${BOLD}${CYAN}Testing Complete.${RESET}\n"