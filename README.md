# Optimal Binary Search Tree (C++)

This project implements an **Optimal Binary Search Tree (OBST)** using **Dynamic Programming**. The goal is to build a binary search tree that minimizes the average search cost for a given set of keys and their access frequencies.

In a typical binary search tree, the structure depends only on the order of insertion. However, if some keys are accessed more frequently than others, the tree can become inefficient. The optimal BST algorithm solves this by placing frequently accessed keys closer to the root, reducing the overall search time on average.

The program calculates the minimum possible cost of searching in the tree and determines which key should be the root of each subtree. It uses a bottom-up dynamic programming approach that explores all possible root choices and selects the configuration with the lowest expected cost.

This algorithm is commonly used in compiler design, database indexing, and data compression, where minimizing average access time is crucial for performance.
