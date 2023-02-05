#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter a positive integer: ";
    cin >> n;

    int digit, even, odd, num;
    for (int i = 1; i <= n; i++)
    {
        
        even = odd = 0;
        num = i;
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
        if (even > odd)
        {
            cout << i << endl;
        }
    }

    return 0;
}
