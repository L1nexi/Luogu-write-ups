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
下确界为最大的下界。故可以利用二分法求解。对每一个下界，试图寻早比它更大的下界，直到找到最大的下界。
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