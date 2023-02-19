# include <iostream>
# include <cmath>
using namespace std;

void printDivisors(int num);

const char SPACE = ' ';

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
    string divisors;
    if (pow(div, 2) == num)
    {
        divisors = to_string(div) + SPACE;
        div--;   
    }
    else
        divisors = "";

    while (div >= 1)
    {
        if (num % div == 0)
        {
            divisors = to_string(div) + SPACE + divisors + to_string(num / div) + SPACE;
        }
        div--;
    }
    cout << divisors;
}