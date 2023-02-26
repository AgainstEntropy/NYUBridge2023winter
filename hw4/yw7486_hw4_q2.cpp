#include <iostream>
using namespace std;

const int   I = 1,
            V = 5,
            X = 10,
            L = 50,
            C = 100,
            D = 500,
            M = 1000;

int main()
{
    int numDecimal;
    cout << "Enter decimal number: ";
    cin >> numDecimal;

    cout << numDecimal << " is ";
    while (numDecimal > 0)
    {
        if (numDecimal >= M)
        {
            cout << 'M';
            numDecimal -= M;
        }
        else if (numDecimal >= D)
        {
            cout << 'D';
            numDecimal -= D;
        }
        else if (numDecimal >= C)
        {
            cout << 'C';
            numDecimal -= C;
        }
        else if (numDecimal >= L)
        {
            cout << 'L';
            numDecimal -= L;
        }
        else if (numDecimal >= X)
        {
            cout << 'X';
            numDecimal -= X;
        }
        else if (numDecimal >= V)
        {
            cout << 'V';
            numDecimal -= V;
        }
        else if (numDecimal >= I)
        {
            cout << 'I';
            numDecimal -= I;
        }
    }

    return 0;
}
