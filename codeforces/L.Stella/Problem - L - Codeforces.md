[Problem - L - Codeforces](https://codeforces.com/gym/105930/problem/L)

L. Stella

time limit per test: 1 second

memory limit per test: 1024 megabytes

input: standard input

output: standard output

In astronomy, stellar classification is the classification of stars based on their spectral characteristics. Most stars are currently classified under the Morgan-Keenan (MK) system using the letters O, B, A, F, G, K, and M, a sequence from the hottest (O type) to the coolest (M type). Each letter class is then subdivided using a numeric digit with 0 being hottest and 9 being coolest. For example, A8, A9, F0, and F1 form a sequence from hotter to cooler.

It obvious that $7$ letters and $10$ digits give us a total of $70$ different classes, where O0 is the hottest and M9 is the coolest. Given two classes, determine if the first class is hotter than, cooler than, or the same with the second class.

**Input**

There are multiple test cases. The first line of the input contains an integer $T$ ($1 \le T \le 10^3$), indicating the number of test cases. For each test case:

The first and only line contains two strings of length $2$, indicating the two classes.

**Output**

For each test case output one line.

-   If the first class is hotter than the second class, output hotter.
-   If the first class is cooler than the second class, output cooler.
-   If the first class is the same with the second class, output same.