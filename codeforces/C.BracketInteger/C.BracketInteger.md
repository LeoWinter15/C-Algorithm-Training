[Problem - C - Codeforces](https://codeforces.com/gym/105930/problem/C)

C. Bracket Integer

time limit per test: 1 second

memory limit per test: 1024 megabytes

input: standard input

output: standard output

Let $(_w$ and $)_w$ be a round bracket of weight $w$. Define the balanced weighted bracket sequence (BWBS) as follows:

-   An empty sequence is a BWBS.
-   If $P$ is a BCBS, then $(_wP)_w$ is also a BCBS. That is, the two brackets at the beginning and the end have the same weight.
-   If $P$ and $Q$ are both BWBS, then $PQ$ is also a BWBS.

For example, $(_1(_3)_3)_1$ and $(_5(_7)_7(_2)_2)_5$ are both BWBS, while $(_1(_3)_1)_3$ and $)_5(_5(_7)_7$ are not.

Consider a positive integer with $n$ digits without leading zeros, where its $i$\-th most significant digit is $d_i$ (that is, the integer is equal to $\sum\limits_{i = 1}^n d_i \times 10^{n - i}$). We say the integer is a bracket integer, if there exists a balanced weighted bracket sequence where the $i$\-th bracket has weight $d_i$. For example, $1000022122$ is a bracket integer, as there exists such BWBS $(_1(_0(_0)_0)_0(_2)_2)_1(_2)_2$.

Given an integer $A$, find the largest bracket integer smaller than or equal to $A$.

**Input**

There are multiple test cases. The first line of the input contains an integer $T$ ($1 \le T \le 10^4$), indicating the number of test cases. For each test case:

The first and only line contains an integer $A$ ($11 \le A \lt 10^{2 \times 10^5}$).

It's guaranteed that the total number of digits of $A$ of all test cases does not exceed $2 \times 10^5$.

**Output**

For each test case output one line containing one integer, indicating the largest bracket integer smaller than or equal to $A$. As $11$ is a bracket integer, the answer always exists. Note that bracket integers must not have leading zeros.

# Example

## Input

```
4
20250525
11451419198100
1001
1000
```

## output

```
20244202
11451418814154
1001
99
```

