*This project was created as part of the 42 curriculum by xiribar.*

![Push Swap Badge](https://github.com/ayogun/42-project-badges/blob/main/badges/push_swapm.png?raw=true)

# Push Swap

Push Swap is an algorithmic sorting project written in C. The program sorts integers with two stacks and a restricted set of operations while minimizing the number of emitted instructions.

## Approach

I implemented a cost-based Turk algorithm:

1. Move values from stack A to stack B while preserving useful ordering.
2. Sort the final three values in A.
3. Calculate the insertion target and movement cost for every value in B.
4. Select the cheapest move.
5. Combine rotations with rr or rrr whenever possible.
6. Rotate the minimum value to the top of A.

This approach turns the problem into repeated local optimization while keeping operation counts within the project's performance constraints.

## Performance

| Input size | Project threshold | Typical result |
|---:|---:|---:|
| 3 | fewer than 3 operations | 1–2 |
| 5 | fewer than 12 operations | about 9 |
| 100 | fewer than 700 operations | about 580 |
| 500 | fewer than 5,500 operations | about 4,800 |

Results vary with the input permutation.

## Build and use

~~~bash
make
./push_swap 4 67 3 87 23
~~~

Count the generated operations:

~~~bash
ARG="4 67 3 87 23"
./push_swap $ARG | wc -l
~~~

## What this project demonstrates

- Algorithmic reasoning under a constrained instruction set
- Linked-list and stack manipulation in C
- Input validation and edge-case handling
- Cost modeling and operation optimization
- Memory management and automated testing

AI assisted with the tester script. The sorting implementation was reviewed and tested manually against the project requirements.

## Contact

[LinkedIn](https://ch.linkedin.com/in/xabier-iribar-revuelta-b85b09320) · [Portfolio](https://xabieriribar.com)
