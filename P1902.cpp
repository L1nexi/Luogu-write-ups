#include <iostream>
#include <cctype>
#include <climits>
#include <queue>
#include <cstring>

using namespace std;
inline bool inArea(int x,int y,int xlim, int ylim)
{
    return x >= 0 && x <= xlim && y >= 0 && y <= ylim;
}
// 快读
int getInt();
bool BFS(int n, int m ,int *arr, int *isUsed, int maxHarm);
// 控制上下左右的网格
int xMove[] = {-1, 0, 1, 0};
int yMove[] = {0, 1, 0, -1};
int main(void)
{
    int m, n;
    cin >> n >> m;
    int arr[n][m] = {};
    int isUsed[n][m] = {};
    int tmp, max{INT_MIN};
    for(int i{}; i < n;i++)
    {
        for (int j{}; j < m;j++)
        {
            tmp = getInt();
            arr[i][j] = tmp;
            if (tmp > max)
            {
                max = tmp;
            }
        }
    }

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

    return 0;
}
int getInt()
{
    int f = 1;
    char ch;
    while (isdigit(ch = getchar()) == false)
    {
        if(ch == '-')
            f = -1;
    }

    
    int tmp = ch - '0';
    while(isdigit(ch = getchar()) == 1)
    {
        tmp = tmp * 10 + ch - '0';
    }
    return tmp * f;
}
bool BFS(int n, int m ,int *arr, int *isUsed, int maxHarm)
{
    std:queue<std::pair<int, int>> queue;
    for(int x{}; x < m; ++x)
    {
        queue.emplace(x, 0);
        isUsed[x] = 1;
    }
    while (queue.empty() == false)
    {
        auto tmp = queue.front();
        queue.pop(); 
        for(int k{};k < 4;++k)
        {
            int new_x = tmp.first + xMove[k];
            int new_y = tmp.second + yMove[k];
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