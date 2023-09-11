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
