[Problem - D - Codeforces](https://codeforces.com/gym/105930/problem/D)

D. Distributed System

time limit per test: 1 second

memory limit per test: 1024 megabytes

input: standard input

output: standard output

A distributed system has $n$ worker nodes numbered from $0$ to $(n - 1)$. The system is going to process $q$ tasks, where the $i$\-th task can be represented by two integers $a_i$ and $b_i$, meaning that the task has $a_i$ subtasks numbered from $0$ to $(a_i - 1)$, and subtask $j$ will be assigned to worker $(b_i + j) \bmod n$.

For each $0 \le k \lt n$, calculate the total number of subtasks assigned to worker $k$ after all tasks are processed.

**Input**

There are multiple test cases. The first line of the input contains an integer $T$ ($1 \le T \le 10^4$), indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $q$ ($1 \le n, q \le 2 \times 10^5$), indicating the number of worker nodes and the number of tasks.

For the following $q$ lines, the $i$\-th line contains two integers $a_i$ and $b_i$ ($1 \le a_i \le 10^9$, $0 \le b_i \lt n$), indicating the $i$\-th task.

It's guaranteed that neither the sum of $n$ nor the sum of $q$ of all test cases will exceed $2 \times 10^5$.

**Output**

For each test case output one line containing $n$ integers $v_0, v_1, \cdots, v_{n - 1}$ separated by a space, where $v_k$ is the total number of subtasks assigned to worker $k$ after all tasks are processed.

## input

```
2
7 3
10 0
4 2
21 1
1 2
200 0
100 0
```

## output

```
5 5 6 5 5 5 4
300
```

