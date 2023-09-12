#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
const double eps{1e-7};
double func(const std::vector<double> &poly, double val);
double binSolve(const std::vector<double> &poly, double left, double right);
int main(void)
{

    // std::cout << fixed << setprecision(2) << ans[0] << ' ' << ans[1] << ' ' << ans[2] << endl;

    return 0;
}
double func(const std::vector<double> &poly, double val)
{
    return poly[0] * val * val * val + poly[1] * val * val + poly[2] * val + poly[3];
}
double binSolve(const std::vector<double> &poly, double left, double right)
{
    double mid = (left + right) / 2;
    while (right - left > eps)
    {
        if (func(poly, mid) * func(poly, left) < 0)
            right = mid;
        else
            left = mid;
        mid = (left + right) / 2;
    }
    return left;
}