#include <iostream>
#include <vector>
#include <utility>
#include <stdio.h>
using std::cout, std::cin, std::endl;

void myQuickSort(int arr[], int first, int end);
int main(void)
{
    int test[100005];
    int tmp;

    scanf("%d", &tmp);
    for (int i{0}; i < tmp; i++)
    {
        scanf("%d", test + i);
    }
    myQuickSort(test, 0, tmp - 1);

    printf("%d", test[0]);
    for (int i{1}; i < tmp; i++)
        printf(" %d", test[i]);
    printf("\n");
    return 0;
}
void myQuickSort(int arr[], int first, int end)
{
    if (first >= end)
    {
        return;
    }
    int pivot = arr[first];
    int left{first}, right{end};
    while (left < right)
    {
        while (left < right && arr[right] >= pivot)
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

    // std::cout << arr[0];
    // for (int i{1};i < 10;i++)
    //     std::cout << ' ' << arr[i];
    // std::cout << endl;
    myQuickSort(arr, first, left - 1);
    myQuickSort(arr, left + 1, end);
    return;
}