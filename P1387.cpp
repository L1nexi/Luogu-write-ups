#include <iostream>
#include <algorithm>

using namespace std;
inline int getRecSum(int sum[101][101], int length, int k, int l);
int main(void)
{
    int n,m ;
    cin >> n >> m;
    int arr[101][101] = {0};
    int sum[101][101] = {0};
    for(int i{1};i <= n; ++i)
    {
        for (int j{1}, rowSum{}; j <= m;++j)
        {
            cin >> arr[i][j];
            sum[i][j] = sum[i - 1][j] + rowSum + arr[i][j];
            rowSum += arr[i][j];
        }
    }
    int maxL = min(n, m);

    for (int length = maxL;length >= 1; --length)
    {
        for (int i{0}; i <= n - length; ++i)
        {
            for (int j{0}; j <= m - length; ++j)
            {
                if (length * length == getRecSum(sum, length, i, j))
                {
                    cout << length;
                    return 0;
                }
            }
        }
    }
    cout << 0;

    return 0;
}
// (x, y) 为要求的矩形的左上角的元素坐标
inline int getRecSum(int sum[101][101], int length, int y, int x)
{
    return sum[y][x] + sum[y +length][x + length] - sum[y + length][x] - sum[y][x + length];
}