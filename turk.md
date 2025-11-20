🇹🇷 The Turk Algorithm: A to Z

The "Turk" algorithm (named after the Mechanical Turk) is a greedy algorithm. Its philosophy is simple: "Always make the move that costs the fewest operations right now."

It is efficient because it calculates the cost of moving every single number and only executes the cheapest one.
🏗️ The Core Concept

    Stack A: Starts full. We want to empty it (save for 3 numbers).

    Stack B: Acts as a sorted buffer.

        Crucial Rule: Stack B is always sorted in Descending Order (Biggest number on top, smallest on bottom).

        Why? Because when we push them back to A later (pa), the order reverses, creating an Ascending list in A.

🚀 Phase 1: Initialization (Kickstart)

We cannot calculate targets in Stack B if Stack B is empty.

    Action: Push the first two nodes from A to B (pb, pb).

        It doesn't matter what they are. We just need reference points in B.

    Result: A has N-2 elements, B has 2.

🧠 Phase 2: A → B (The "Cheapest" Loop)

This is the most important part. We loop until only 3 nodes remain in A.
1. Assign Targets

For every single node in A, look at B and ask: "Where do I fit?"

    The Logic: We look for the closest smaller number in B.

    Example: If A has 5 and B has [10, 4, 2].

        5 fits on top of 4. So, 4 is the Target.

    Edge Case: If the number in A is bigger than everything in B (or smaller than everything), its target is the Maximum number in B (so it becomes the new Max/Min).

2. Calculate Cost

For every node in A, calculate how many moves it takes to push it to B correctly.

    Cost A: Moves to get the node to the top of A (ra or rra).

    Cost B: Moves to get its Target to the top of B (rb or rrb).

    Total Cost: Cost A + Cost B.

3. The Secret Sauce: Simultaneous Moves

If both the Node (in A) and the Target (in B) are in the top half of their stacks, we can use rr to rotate both at once. This saves moves!

    If both are in the bottom half, we use rrr.

4. Execute

    Find the node with the lowest total cost.

    Rotate A and B (using rr/rrr where possible) until the node is at top of A and target is at top of B.

    Push (pb).

🥉 Phase 3: Sort the Last Three

Once A has only 3 nodes left:

    Stop pushing to B.

    Use a simple "Sort Three" function to organize these 3 numbers in A.

        Result: A is now sorted (e.g., [1, 2, 3]).

📦 Phase 4: B → A (The Return)

Now Stack B is full and sorted (Descending), and Stack A has 3 sorted small numbers. We need to move everything back.

We do NOT calculate costs here. We just do it one by one.
The Loop (Until B is empty):

    Identify Node: Look at the top node of B.

    Find Target in A: Look for the closest larger number in A.

        Why larger? Because we are inserting valid numbers into a sorted list.

        Example: B top is 6. A is [1, 2, 10].

        6 needs to go before 10. So 10 is the target.

    Rotate A: Rotate A (ra or rra) until the Target (10) is at the top.

    Push (pa): Move 6 to A.

        A becomes [6, 1, 2, 10] (Note: It's still sorted circularly!).

🏁 Phase 5: Final Adjustment

Stack A is now fully sorted, but the start point might be wrong (rotated).

    Current State: [4, 5, 1, 2, 3]

    Goal: [1, 2, 3, 4, 5]

    Find the index of the smallest number (1).

    If it's above the median, ra until it's at the top.

    If it's below the median, rra until it's at the top.

🎉 DONE.
📝 Summary of Logic flow

    pb x 2.

    While (size A > 3):

        Update positions.

        Match A nodes to B targets (Closest Smaller).

        Calc costs (find cheapest).

        Rotate A & B to positions.

        pb.

    Sort Three (Stack A).

    While (B is not empty):

        Match B top to A target (Closest Larger).

        Rotate A to position.

        pa.

    Final Rotation (Bring min to top).
