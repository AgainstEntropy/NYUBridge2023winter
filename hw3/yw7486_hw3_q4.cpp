#include <iostream>
using namespace std;

const int FLOOR_ROUND = 1;
const int CEILING_ROUND = 2;
const int ROUND = 3;

int main()
{
    double realNum;
    int roundMethod, wholeNum;

    cout << "Please enter a Real number:\n";
    cin >> realNum;
    cout    << "Choose your rounding method:\n"
            << "1. Floor round\n"
            << "2. Ceiling round\n"
            << "3. Round to the nearest whole number\n";
    cin >> roundMethod;

    switch (roundMethod)
    {
    case FLOOR_ROUND:
        wholeNum = realNum;
        break;
    case CEILING_ROUND:
        wholeNum = realNum + 1;
        break;
    case ROUND:
        wholeNum = realNum + 0.5;
        break;
    default:
        break;
    }

    cout << wholeNum << endl;

    return 0;
}
