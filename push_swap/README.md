# Push_Swap

## Overview

Push_Swap is a project that involves sorting a stack of integers using a limited set of operations. The goal is to sort the stack in ascending order with the fewest number of operations possible. The project is typically implemented in C and involves understanding and manipulating linked lists, sorting algorithms, and optimization techniques.

## Operations

The following operations are used to manipulate the stacks:

- `sa`: Swap the first two elements of stack A.
- `sb`: Swap the first two elements of stack B.
- `ss`: Perform `sa` and `sb` simultaneously.
- `pa`: Push the top element of stack B to stack A.
- `pb`: Push the top element of stack A to stack B.
- `ra`: Rotate stack A (shift all elements up by one, the first element becomes the last).
- `rb`: Rotate stack B (shift all elements up by one, the first element becomes the last).
- `rr`: Perform `ra` and `rb` simultaneously.
- `rra`: Reverse rotate stack A (shift all elements down by one, the last element becomes the first).
- `rrb`: Reverse rotate stack B (shift all elements down by one, the last element becomes the first).
- `rrr`: Perform `rra` and `rrb` simultaneously.

## Sorting Algorithm

The sorting algorithm implemented in this project involves the following steps:

1. **Initialization**: Parse the input arguments and initialize the stacks.

2. **Sorting Small Stacks**:
   - If the stack has 2 elements, use `sa` to sort it.
   - If the stack has 3 elements, use a specific algorithm to sort it.

3. **Sorting Larger Stacks**:
   - Push elements from stack A to stack B until only three elements remain in stack A.
   - Sort the remaining three elements in stack A.
   - Push elements back from stack B to stack A in the correct order.

4. **Final Adjustment**: Ensure the smallest element is at the top of stack A.

The algorithm uses a combination of rotations, pushes, and swaps to achieve the sorted stack with the minimum number of operations.