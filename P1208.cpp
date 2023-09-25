#include <iostream>
#include <algorithm>

using namespace std;
struct Peasant
{
    public:
        int price{};
        int amount{};
    bool operator<(const Peasant &rhs) const {
    return price < rhs.price;
}
    /* data */
};

std::istream& operator>>(std::istream &is, Peasant &tgt)
{
    is >> tgt.price;
    is >> tgt.amount;
    return is;
}

int main(void)
{
    int n, m;
    Peasant arr[5000];
    cin >> n >> m;
    for (int i{};i < m; ++i)
    {
        cin >> arr[i];
    }
    sort(arr, arr + m);
    int  totp{0};
    int i{0};
    while (n > 0)
    {
        if (n >= arr[i].amount)
        {
            n -= arr[i].amount;
            totp += arr[i].amount * arr[i].price;
        }
        else
        {
            totp += n * arr[i].price;
            n = 0;
        }
        ++i;
    }
    cout << totp;
    return 0;
}