#include <iostream>

using namespace std;
void outputIn2pow(int n);
int main(void)
{
    int n;
    cin >> n;
    outputIn2pow(n);
    cout << endl;
    return 0;
}
void outputIn2pow(int n)
{
    if (n == 0)
    {
        cout << "0";
        return;
    }
    else if (n == 1)
    {
        return;
    }
    int mask = 0x8000;
    int i = 15; //掩码的最高位编号为 15
    int bit;
    while(i >= 0 && n > 0)
    {
        bit = mask & n;
        // 如果这一位不为 0
        if (bit != 0)
        {
            if (i != 1)
            {
                cout << "2(";
                outputIn2pow(i);
                cout << ")";
            }
            else
            {
                cout << "2";
                outputIn2pow(i);
            }
            // 已处理该位，将其置为 0
            n = n & (~bit);
            if (n != 0)
            {
                cout << "+";
            }
        }
        --i;
        mask >>= 1;
    }
}