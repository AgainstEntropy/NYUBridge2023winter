# include <iostream>
# include <cmath>
using namespace std;

void printDivisors(int num);

const char space = ' ';

int main()
{
    cout << "Please enter a positive integer >= 2: ";
    int integer;
    cin >> integer;

    printDivisors(integer);

    return 0;
}

void printDivisors(int num)
{
    int div = sqrt(num);
    string divisors = to_string(div);
    if (pow(div, 2) != num)
    {
        divisors += (space + to_string(num / div));
    }

    while (--div >= 1)
    {
        if (num % div == 0)
        {
            divisors = to_string(div) + space + divisors + space + to_string(num / div);
        }
    }
    cout << divisors;
}