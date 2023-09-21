### 洛谷题解以及解析（可能）

##### P1177 【模板】快速排序
本题是一道排序题，这边实现了一个递归快速排序算法。
思路：首先选取一个基准数，然后将比基准数小的数放在左边，比基准数大的数放在右边，然后在两侧递归左右两边的数，直到排序完成。
```c++
void myQuickSort(int arr[], int first, int end)
{
    if (first >= end)
    {
        return;
    }
    int pivot = arr[first];     //选取基准数
    int left{first}, right{end};
    while (left < right)        //当左右两侧相遇时，一次排序完成
    {
        while (left < right && arr[right] >= pivot) //注意要让右侧先动，这样可以保证后续基准数与left交
                                                    //换时，基准数始终大于等于 left
        {
            --right;
        }
        while (left < right && arr[left] <= pivot)
        {
            ++left;
        }
        arr[left] = std::exchange(arr[right], arr[left]);
    }
    arr[first] = std::move(arr[left]);
    arr[left] = std::move(pivot);

    myQuickSort(arr, first, left - 1);
    myQuickSort(arr, left + 1, end);
    return;
}
```

##### P1024 一元三次方程求根
本题利用二分法求近似解。由于限制了两个根之差大于 1 ，可以以 0.5 为间隔寻找符号改变时的自变量取值。

##### P2678 跳石头
注意到本题需求最小跳跃距离的最大值。即为 $max(mix(jumpLength))$，实际上，这就是要求 $jumpLength$ 的下确界,
下确界为最大的下界。故可以利用二分法求解。对每一个下界，试图寻找比它更大的下界，直到找到最大的下界。
```c++
bool isOk(int arr[], int n, int m, int maxminjmp)
{
    int cnt{0};
    int prev{0};
    for(int i = 1;i <= n + 1;i++)
    {
        if (arr[i] - arr[prev] < maxminjmp)
        {
            ++cnt;
        }
        else
        {
            prev = i;
        }
    }
    return cnt <= m;
}
```
```c++
    // left <= right，防止漏掉 left == right时候的解
    while (left <= right)
    {
        if (isOk(arr, n, m, mid) == true)   // 为下界，尝试寻找更大的下界
        {
            ans = mid;
            left = mid + 1;
        }
        else    //非下界
        {
            right = mid - 1;
        }
        mid = (left + right) / 2;
    }
    cout << ans;

```

##### P1902 刺杀大使
本题为考察二分法查找以及 BFS 搜索，这边概述 DFS 搜索和 BFS 搜索。

DFS， Depth First Search， 深度优先搜索：DFS会尽量深的搜索某个分支，直到无法继续搜索或搜索完成，然后回溯到上一个节点，继续搜索其他分支。可以通过 Stack 和记录已搜索节点的数组来实现 DFS 搜索。

BFS, Breadth First Search，广度优先搜索：BFS 不会一次性深入进入某个分支，而是将每个节点的分支都记录下来,在下一层的遍历中依次处理。可以用水源来比喻 BFS 的开始节点，存在通路的地方都会有水流入，直到搜索完成。
```c++
    // 二分查找
    int left{0}, right{max};
    int mid = (left + right ) / 2;
    int ans = mid;
    while (left <= right)
    {
        // 用 BFS 判断当前解是否成立
        if (BFS(n, m, arr[0], isUsed[0], mid) == true)
        {
            ans = mid;
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
        mid = (right + left) / 2;
    }
    cout << ans;

```
```c++
bool BFS(int n, int m ,int *arr, int *isUsed, int maxHarm)
{
    std:queue<std::pair<int, int>> queue;
    // 设置搜索开始的节点。 与DFS不同，BFS可以有多个开始节点
    for(int x{}; x < m; ++x)
    {
        queue.emplace(x, 0);
        isUsed[x] = 1;
    }
    // 如果还有没处理的节点，继续循环
    while (queue.empty() == false)
    {
        auto tmp = queue.front();
        queue.pop(); 
        for(int k{};k < 4;++k)
        {
            int new_x = tmp.first + xMove[k];
            int new_y = tmp.second + yMove[k];
            // 如果没有越界、没有被访问过、满足搜索要求，则添加到下次搜索的队列中
            if (inArea(new_x, new_y, m - 1, n - 1) == true && isUsed[new_y * m + new_x] == 0 && arr[new_y * m + new_x] <= maxHarm)
            {
                queue.emplace(new_x, new_y);
                isUsed[new_y * m + new_x] = 1;
            }
        }
    }
    int tmp = isUsed[m * n - 1];
    // 将 isUsed 数组清零
    memset(isUsed, 0, m * n * sizeof(int));
    return tmp;
}
```
##### P1226 「模板」快速幂 || 取余运算
本题要求计算 $a^b\enspace mod \enspace p$。在不考虑取模的情况下，考虑 $a^b$
我们可以注意到 $b$ 的二进制存储方式提供了天然的分解 $a^b$ 的方式:

$$
b = (d_{r-1}······d_1d_0)_2 = \sum_{i = 0}^{r - 1}2^i * d_i \\
a^b =\prod_{i = 0}^{r - 1} a^{2 ^ i * d_i}
$$

同时有性质 $a^{2^{i + 1}} = a^{2 ^ i} * a^{2 ^ i}$，可以由低次向高次迭代。
通过这种方式计算可以将时间复杂度降低为 $O(logn)$
```c++
    long long base = a % p; 
    long long ans{1}; 
    while (power > 0)
    {
        if (power & 0x1)
        {
        ans = (ans * base) % p;
        }
        base = (base * base) % p;
        power >>= 1;
    }
```

##### P1010 幂次方
本题给定一个整数，要求输出这个数符合规定的 2 和 0表示，如 $137$ 可表示为 $2(7)+2(3)+2(0)$。
进一步：$7= 2^2+2+2^0$  ( $2^1$ 用 $2$ 表示)，并且 $3=2+2^0$。
所以最后 $137$ 可表示为 $2(2(2)+2+2(0))+2(2+2(0))+2(0)$。
这道题可以通过分治和递归的方式解决。通过二进制表示可以得到一个数的 2 的幂次表示，而对这个幂次表示又可以得到它的幂次表示。
这是一个递归的过程。
需要注意对输出格式的控制。只要还有项没有处理，在每一项处理完成后打印 `‘+’` 即可。
```c++
void outputIn2pow(int n)
{
    if (n == 0)
    {
        cout << "0";
        return;
    }
    else if (n == 1)
    {
        return;
    }
    int mask = 0x8000;
    int i = 15; //掩码的最高位编号为 15
    int bit;
    while(i >= 0 && n > 0)
    {
        bit = mask & n;
        // 如果这一位不为 0
        if (bit != 0)
        {
            if (i != 1)
            {
                cout << "2(";
                outputIn2pow(i);
                cout << ")";
            }
            else
            {
                cout << "2";
                outputIn2pow(i);
            }
            // 已处理该位，将其置为 0
            n = n & (~bit);
            if (n != 0)
            {
                cout << "+";
            }
        }
        --i;
        mask >>= 1;
    }
}
```