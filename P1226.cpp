#include <iostream>

using std::cin, std::cout, std::endl;
int main(void)
{
    long long a, b, p;
    std::cin >> a >> b >> p;
    long long power = b;
    
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
    cout << a << '^' << b << " mod " << p << '=' << ans <<endl;

    return 0;
}