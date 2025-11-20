📝 READ THIS TOMORROW: Push_swap Implementation Plan
1. Immediate Code Cleanup

Fix swap_two: Add a safety check to ensure the list has at least 2 nodes before accessing next.

Refactor sort_three: Replace your current "put biggest in bottom" logic.

If max is at top: ra.

If max is in middle: rra.

    Then, if first > second: sa.

    Fix find_biggest_index: Ensure *index is initialized to the first node's index, not left as garbage value.

2. Implement the "Move" Function (The missing link)

Create a function (e.g., execute_move) that takes the cheapest node as an argument.

Check for Double Rotations (rr/rrr):

If the cheapest node needs to go UP in A AND its target needs to go UP in B: perform rr until one is at the top.

    If both need to go DOWN: perform rrr.

Finish Single Rotations:

Rotate A until the cheapest node is at the top (0).

    Rotate B until the target node is at the top (0).

    Push: Finally, perform pb.

3. Phase 1: A to B (The "Brain" Loop)

Logic: Push everything to B except the last 3 nodes, keeping B sorted descending.

Initialization:

    Push the first 2 nodes from A to B blindly (to have something to compare against).

The Loop (while size of A > 3):

Update Indices: Refresh the index value for every node in A and B.

Assign Targets: For every node in A, find the "closest smaller number" in B.

Calculate Costs:

Cost A: Distance to top of A.

Cost B: Distance of Target to top of B.

    Total Cost = moves in A + moves in B (accounting for shared rr/rrr moves).

Find Cheapest: Pick the node with the lowest total cost.

        Execute Move: Call the function created in Step 2.

4. Phase 2: Sort the Remaining 3

    Call your fixed sort_three function on the 3 nodes left in Stack A.

5. Phase 3: B to A (The "Unload")

Logic: Move everything back to A. No cost calculation needed.

The Loop (while B is not empty):

Update Indices: Refresh index for A and B.

Find Target: For the top node of B, find the "closest larger number" in A.

Rotate A: Rotate Stack A (using ra or rra) until that target node is at index 0.

        Push: Perform pa.

6. Phase 4: Final Adjustment

The list is now sorted, but the smallest number might not be at the top (e.g., 3 4 5 1 2).

Find the node with the smallest number.

If it is above the median: ra until it is at the top.

    If it is below the median: rra until it is at the top.

⚠️ Critical Logic Reminders

    Never push from A to B without rotating B to the correct position first.

    Do not calculate costs for the B to A phase; just match the top of B to its spot in A.

    Update indices (current_pos) every time you modify the stacks (after any push or full rotation sequence).
