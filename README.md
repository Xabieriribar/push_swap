*This project has been created as part of the 42 curriculum by xiribar.*

![Push Swap Badge](https://github.com/ayogun/42-project-badges/blob/main/badges/push_swapm.png?raw=true)

# PUSH_SWAP: ALGORITHMIC SORTING ENGINE
*42 Lausanne, Switzerland*

## 01. ABOUT
This project is a deep dive into algorithmic complexity and stack manipulation. The goal is simple: sort a random set of integers using two stacks (**Stack A** and **Stack B**) and a specific set of operations. The challenge lies in the constraint: minimizing the number of instructions.

I implemented the **Turk Algorithm** (Mechanical Turk). Instead of recursive methods like QuickSort, this is a greedy algorithm that calculates the "cheapest" move for every node at every step, ensuring highly optimized operation counts for large datasets.

## 02. THE LOGIC

### PHASE 1: PARTITIONING
*   **Push to B:** Move all nodes from A to B, leaving only 3 elements.
*   **Pre-sorting:** While pushing, I check median values. If a node is smaller than the median, I rotate B to place it at the bottom.
*   **Tiny Sort:** Instantly sort the remaining 3 numbers in Stack A.

### PHASE 2: MECHANICAL TURK
*   **Cost Calculation:** For every node in B, I calculate the moves required to put it in position in A.
*   **Cheapest Move:** I select the node with the absolute lowest cost.
*   **Simultaneous Rotation:** I utilize `rr` and `rrr` to move both stacks at once, saving instructions.

## 03. TECHNOLOGY STACK

!C
!Makefile
!Bash
!Git

## 04. PERFORMANCE METRICS

| Stack Size | Constraint (Max Ops) | My Algorithm (Avg Ops) |
| :--- | :--- | :--- |
| **3 Numbers** | < 3 | **1-2** (Hardcoded) |
| **5 Numbers** | < 12 | **9** (Average) |
| **100 Numbers** | < 700 | **~580** |
| **500 Numbers** | < 5500 | **~4800** |

## 05. USAGE

### 1. Clone and Compile

```bash
git clone git@github.com:Xabieriribar/push_swap.git
cd push_swap
make
```

### 2. Run with Integers

```bash
./push_swap 4 67 3 87 23
```

### 3. Check Operations Count

```bash
ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l
```

## 06. FILE STRUCTURE
> *The project follows a strict 42-Norminette compliant structure, separating operations, sorting logic, and parsing utilities.*

## 07. CONTACT

[!LinkedIn](https://ch.linkedin.com/in/xabier-iribar-revuelta-b85b09320)
[!Portfolio](https://xabieriribar.com)
[!Email](mailto:xabieriribarrevuelta@gmail.com)

© 2024 Xabier Iribar Revuelta. All Rights Reserved.
