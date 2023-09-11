#include <iostream>
#include <vector>
#include <map>
#include <string>
using std::cout, std::cin, std::endl;
int result[5][5] = {
    {0, -1, 1, 1, -1,},
    {1,  0, -1, 1, -1,},
    {-1, 1, 0, -1, 1,},
    {-1, -1, 1, 0, 1,},
    {1, 1, -1, -1, 0,},
};
int main(void)
{
    int gameTime;
    int Alp, Blp;
    cin >> gameTime >> Alp >> Blp;
    std::vector<int> Achoice, Bchoice;
    for (int i{0}, tmp; i < Alp; i++)
    {
        cin >> tmp;
        Achoice.emplace_back(tmp);
    }
    for (int i{0}, tmp; i < Blp; i++)
    {
        cin >> tmp;
        Bchoice.emplace_back(tmp);
    }
    int Atot{0}, Btot{0};
    for (int i{0}, choice; i < gameTime; i++)
    {
        choice = result[Achoice[i % Alp]][Bchoice[i % Blp]];
        switch(choice)
        {
            case 1:
            ++Atot;
            break;
            case -1:
            ++Btot;
            break;
            default:
            break;
        }
    }
    cout << Atot << ' ' << Btot << endl;

    return 0;
}