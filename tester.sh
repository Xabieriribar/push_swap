#!/bin/bash

# ==============================================================================
#                          PUSH_SWAP ULTIMATE TESTER
# ==============================================================================

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
BOLD='\033[1m'
NC='\033[0m'

PROG="./push_swap"
CHECKER=""

# ------------------------------------------------------------------------------
# 1. SETUP & DETECTION
# ------------------------------------------------------------------------------

echo -e "${BLUE}${BOLD}>>> SETTING UP...${NC}"

# Compile
make re > /dev/null 2>&1
if [ ! -f "$PROG" ]; then
    echo -e "${RED}Error: $PROG not found. compilation failed.${NC}"
    exit 1
fi

# Detect Checker
if [ -f "./checker_linux" ]; then
    CHECKER="./checker_linux"
elif [ -f "./checker_Mac" ]; then
    CHECKER="./checker_Mac"
elif [ -f "./checker" ]; then
    CHECKER="./checker"
else
    echo -e "${YELLOW}Warning: No checker binary found (checker_linux/checker_Mac). Verification will rely on instruction count only.${NC}"
fi

echo -e "${GREEN}Executable: $PROG${NC}"
if [ -n "$CHECKER" ]; then echo -e "${GREEN}Checker:    $CHECKER${NC}"; fi
echo ""

# ------------------------------------------------------------------------------
# 2. ERROR MANAGEMENT TESTS
# ------------------------------------------------------------------------------
echo -e "${BLUE}${BOLD}>>> TESTING ERROR MANAGEMENT${NC}"

# Helper function for errors
check_error() {
    NAME=$1
    ARGS=$2
    OUTPUT=$($PROG $ARGS 2>&1)
    
    if echo "$OUTPUT" | grep -q "Error"; then
        echo -e "  ${GREEN}[OK]${NC} $NAME"
    else
        echo -e "  ${RED}[KO]${NC} $NAME (Expected 'Error', got: '$OUTPUT')"
    fi
}

check_error "Non-numeric input" "1 2 one 4"
check_error "Duplicate numbers" "1 2 3 2 5"
check_error "Max Int Overflow" "1 2 2147483648 4"
check_error "Min Int Underflow" "1 2 -2147483649 4"

echo ""

# ------------------------------------------------------------------------------
# 3. IDENTITY TESTS (Already Sorted)
# ------------------------------------------------------------------------------
echo -e "${BLUE}${BOLD}>>> TESTING IDENTITY (Already Sorted)${NC}"

check_identity() {
    ARGS=$1
    OPS=$($PROG $ARGS | wc -l | tr -d ' ')
    if [ "$OPS" -eq 0 ]; then
         echo -e "  ${GREEN}[OK]${NC} Args: \"$ARGS\" -> 0 instructions"
    else
         echo -e "  ${RED}[KO]${NC} Args: \"$ARGS\" -> $OPS instructions (Should be 0)"
    fi
}

check_identity "42"
check_identity "1 2 3"
check_identity "1 2 3 4 5"
echo ""

# ------------------------------------------------------------------------------
# 4. SIMPLE SORTS (3 and 5)
# ------------------------------------------------------------------------------
echo -e "${BLUE}${BOLD}>>> TESTING SIMPLE SORTS (3 & 5)${NC}"

run_test() {
    COUNT=$1
    LIMIT=$2
    ITERATIONS=$3
    
    TOTAL_OPS=0
    MAX_OPS=0
    FAILED=0
    
    echo -ne "Testing $COUNT random numbers ($ITERATIONS runs)... "
    
    for ((i=0; i<ITERATIONS; i++)); do
        # Generate random numbers using Ruby (Standard on 42 machines)
        ARG=$(ruby -e "puts (1..$COUNT).to_a.shuffle.join(' ')")
        
        # Run Push_swap
        OPS=$($PROG $ARG | wc -l | tr -d ' ')
        
        # Run Checker
        if [ -n "$CHECKER" ]; then
            CHECK_RES=$($PROG $ARG | $CHECKER $ARG)
            if [ "$CHECK_RES" != "OK" ]; then
                echo -e "\n${RED}[KO] Checker failed on sorting!${NC}"
                echo "Args: $ARG"
                FAILED=1
                break
            fi
        fi
        
        # Update Stats
        TOTAL_OPS=$((TOTAL_OPS + OPS))
        if [ "$OPS" -gt "$MAX_OPS" ]; then MAX_OPS=$OPS; fi
    done

    if [ $FAILED -eq 0 ]; then
        AVG=$((TOTAL_OPS / ITERATIONS))
        
        COLOR=$GREEN
        if [ "$MAX_OPS" -gt "$LIMIT" ]; then COLOR=$RED; fi
        
        echo -e "${COLOR}Max: $MAX_OPS${NC} (Limit: $LIMIT) | Avg: $AVG"
    fi
}

run_test 3 3 10
run_test 5 12 10
echo ""

# ------------------------------------------------------------------------------
# 5. BENCHMARKS (100 and 500)
# ------------------------------------------------------------------------------
echo -e "${BLUE}${BOLD}>>> TESTING BENCHMARKS (Middle & Advanced)${NC}"

# 100 Numbers - Limit 700
# Grading: 5 stars < 700, 4 stars < 900, etc.
echo -e "${YELLOW}--- 100 Numbers (Limit: 700) ---${NC}"
run_test 100 700 20

# 5