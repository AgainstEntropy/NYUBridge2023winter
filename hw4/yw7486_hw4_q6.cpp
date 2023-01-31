#include <iostream>
using namespace std;

bool qualified(int num);

int main()
{
    int n;
    cout << "Enter a positive integer: ";
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        if (qualified(i))
        {
            cout << i << endl;
        }
    }

    return 0;
}

bool qualified(int num)
{
    int digit;
    int even = 0,
        odd = 0;
    while (num != 0)
    {
        digit = num % 10;
        if (digit % 2)
        {
            odd++;
        }
        else
        {
            even++;
        }
        num /= 10;
    }

    return true ? even > odd : false;
}

// more even digits than odd digits