#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int numDecimal;
    cout << "Enter decimal number: ";
    cin >> numDecimal;

    cout << "The binary representation of " << numDecimal << " is ";
    int digit = log2(numDecimal);

    int power;
    for (; digit >= 0; digit--)
    {
        power = pow(2, digit);
        if (numDecimal >= power)
        {
            cout << 1;
            numDecimal -= power;
        }
        else
        {
            cout << 0;
        }
    }

    return 0;
}
