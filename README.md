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