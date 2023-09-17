#include <iostream>

using namespace std;
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
int main(void)
{
    int len, n, m;
    cin >> len >> n >> m;
    int arr[n + 2];
    arr[0] = 0;
    arr[n + 1] = len;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    // 二分法枚举整数答案
    int left = 1, right = len;
    int mid = (left + right) >> 1;
    int ans = mid;

    // left <= right，防止漏掉 left == right时候的解
    while (left <= right)
    {
        if (isOk(arr, n, m, mid) == true)
        {
            ans = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
        mid = (left + right) / 2;
    }
    cout << ans;

    return 0;
}
