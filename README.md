# 🏆 C-Algorithm-Training

[![Language](https://img.shields.io/badge/language-C++-blue.svg)](.)
[![Standard](https://img.shields.io/badge/std-GNU++17-brightgreen.svg)](.)
[![Platform](https://img.shields.io/badge/platform-洛谷%20%7C%20Codeforces-orange.svg)](.)

> 个人算法竞赛练习代码归档，收录 [洛谷](https://www.luogu.com.cn/) 与 [Codeforces](https://codeforces.com/) 的 C++ 解题代码。

---

## 🛠 编译环境

| 项目         | 配置                           |
| ------------ | ------------------------------ |
| 语言         | C++                            |
| 标准         | **GNU++17**                    |
| 编译器       | g++                            |
| 推荐编译选项 | `-std=c++17 -O2 -Wall -Wextra` |

---

## 🚀 快速开始

```bash
# 克隆仓库
git clone https://github.com/LeoWinter15/C-Algorithm-Training.git
cd C-Algorithm-Training

# 编译并运行
g++ -std=c++17 -O2 -Wall luogu/P5703/P5703.cpp -o P5703
./P5703 < input.txt
```

### 一键编译脚本（utils/run.sh）

```bash
#!/bin/bash
# 用法: ./utils/run.sh <源文件路径>
g++ -std=c++17 -O2 -Wall -Wextra "$1" -o a.out && ./a.out
```

---

## 💡 常用模板

竞赛中高频使用的代码片段：

```cpp
// 万能头文件
#include <bits/stdc++.h>
using namespace std;

// 快读
inline int read() {
    int x = 0, f = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
    while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x * f;
}

// 常用宏定义
#define ll long long
#define pb push_back
#define all(x) (x).begin(), (x).end()
```

---

## 📌 说明

- 代码均为个人练习，不保证最优解，欢迎交流更优做法。
- 如有问题或建议，欢迎提 [Issue](https://github.com/LeoWinter15/C-Algorithm-Training/issues) 或 [PR](https://github.com/LeoWinter15/C-Algorithm-Training/pulls)。

---

## 📄 License

[MIT](LICENSE)
