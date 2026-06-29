# L. Stella — 题解

## 题目大意

恒星光谱分类采用 Morgan-Keenan (MK) 系统，使用字母 O, B, A, F, G, K, M 表示从热到冷的序列，每个字母再细分数字 0~9（0 最热，9 最冷）。例如：A8 → A9 → F0 → F1 是从热到冷的序列。

总共 $7 \times 10 = 70$ 个不同分类，O0 最热，M9 最冷。

给定 $T$ 组询问，每组两个分类字符串（长度均为 2），判断第一个比第二个更热（hotter）、更冷（cooler）还是相同（same）。

## 思路

每个分类可以映射为一个**唯一的整数排名**，排名越小表示越热：

$$\text{rank} = \text{字母下标} \times 10 + \text{数字}$$

其中字母按 `"OBAFGKM"` 顺序，O 下标为 0，M 下标为 6。

- 比较两个排名的数值大小即可：
  - `rank(a) < rank(b)` → `hotter`
  - `rank(a) > rank(b)` → `cooler`
  - `rank(a) = rank(b)` → `same`

### 复杂度分析

- 时间复杂度：$O(T)$，每组询问 $O(1)$ 计算排名并比较。
- 空间复杂度：$O(1)$。

## 关键代码

```cpp
const string letters = "OBAFGKM";

auto rank = [&](const string& s) -> int {
    int letterIdx = static_cast<int>(letters.find(s[0]));
    int digit = s[1] - '0';
    return letterIdx * 10 + digit;
};

int ra = rank(a), rb = rank(b);

if (ra < rb)
    cout << "hotter\n";
else if (ra > rb)
    cout << "cooler\n";
else
    cout << "same\n";
```
