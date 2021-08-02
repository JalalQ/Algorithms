# 0-1 Knapsack Problem

The problem is to fill a bag of fixed capacity with maximum weight given a selection of items with varying weights. Each of the items is to be treated in an atomic 
sense, i.e. it can not be broken down into smaller/ fractional parts.

The algorithm uses the concept of **memoization** to store value, instead of having to recalculate the value for each incremental value.

The algorithm is summarized as follow, where
- *i* is the index of the item.
- *W* is the maximum allowed weight (in total).
- *n* is the total number of items.
- *w* is the integer number between 0<=w<=W.

![image](https://user-images.githubusercontent.com/58306478/127891625-fd02a278-0e3a-476c-bd6e-9d764d38a78a.png)
