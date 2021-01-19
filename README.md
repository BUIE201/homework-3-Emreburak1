# Homework 3

Write a function to calculate the branch with the largest sum of nodes, given a sorted binary tree of integers. 
The function should print the branch with the largest sum and the calculated sum value.

You can use the binary tree code given in the Lecture as you like.


Example: given the following tree, the function should print.

>Branch with the largest sum is: 5 4 11 7 -> SUM = 27



              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1

### List of branches:

- **branch 1:** 5 4 11 7   ->   SUM = 27 (*)
- **branch 2:** 5 4 11 2   ->   SUM = 22
- **branch 3:** 5 8 13     ->   SUM = 26
- **branch 4:** 5 8 4 1    ->   SUM = 18