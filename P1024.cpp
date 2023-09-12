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

    std::vector<double> poly;
    for (int i = 0; i < 4; ++i)
    {
        double tmp;
        std::cin >> tmp;
        poly.emplace_back(tmp);
    }
    double prev;
    std::vector<double> points;
    std::vector<double> ans;

    double it = -200.0;
    prev = func(poly, -200.5);
    while (prev * func(poly, it) > 0.0)
    {
        it = it + 0.5;
    }
    points.emplace_back(it - 0.5);
    it += 0.5;
    prev = func(poly, it);
    while (prev * func(poly, it) > 0.0)
    {
        it  = it + 0.5;
    }
    points.emplace_back(it - 0.5);
    it += 0.5;
    prev = func(poly, it);
    while (prev * func(poly, it) > 0.0)
    { 
        it = it + 0.5;
    }
    points.emplace_back(it - 0.5);
    points.emplace_back(it + 1);
    for(int i{0}; i < 3; ++i)
    {
        ans.emplace_back(binSolve(poly, points[i], points[i + 1]));
    }
    std::cout << fixed << setprecision(2) << ans[0] << ' ' << ans[1] << ' ' << ans[2] << endl;

    // std::vector<double> poly{1.0, -5.0, -4.0, 20};
    // std::cout << binSolve(poly, -2.5, 1.5) << endl;

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
        if (func(poly, mid) < eps && func(poly, mid) > -eps)
            return mid;
        if (func(poly, mid) * func(poly, left) <= 0)
            right = mid;
        else if(func(poly, mid) * func(poly, right) <= 0)
            left = mid;
        mid = (left + right) / 2;
    }
    return left;
}