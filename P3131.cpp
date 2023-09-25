#include <iostream>
#include <stdio.h>

using namespace std;

int main(void)
{
    int n;
    int arr[50010] = {0};
    int sum[50010] = {0};

    // 第一个元素较为特殊，因为 sum[0] = 0，first[0] 可以确定为 0
    int first[7] = {0, 7, 7, 7, 7, 7, 7};
    int last[7] = {0, 7, 7, 7, 7, 7, 7};

    cin >> n;
    for (int i{1}; i <= n; ++i)
    {
        scanf("%d", arr + i);
        arr[i] %= 7;
        sum[i] = (sum[i - 1] + arr[i]) % 7;
        if (sum[i] != 0 && first[sum[i]] == 7)
        {
            first[sum[i]] = i;
        }
    }
    for (int i{0}; i < 7; ++i)
    {
        if (first[i] != 7)
        {
            for (int j{n}; j >= 1; --j)
            {
                if (sum[j] == i)
                {
                    last[i] = j;
                    break;
                }
            }
        }
    }
    int max = last[0];
    for (int i {1};i < 7; ++i)
    {
        if (first[i] != 7 && last[i] - first[i] > max)
        {
            max = last[i] - first[i];
        }
    }

    cout << (max == -1 ? 0 : max) << std::endl;
    return 0;
}