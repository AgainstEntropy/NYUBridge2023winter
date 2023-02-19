# include <iostream>
using namespace std;

void printShiftedTriangle(int n, int m, char symbol);
void printPineTree(int n, char symbol);

const char SPACE = ' ';

int main()
{
    cout    << "Please enter a positive integer and a character to draw a tree!\n"
            << "The positive integer: ";
    int num;
    cin >> num;

    cout << "The character: ";
    char character;
    cin >> character;

    printPineTree(num, character);

    return 0;
}

void printShiftedTriangle(int n, int m, char symbol)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < n - i + m; j++)
        {
            cout << SPACE;
        }
        for (int j = 1; j <= 2 * i - 1; j++)
        {
            cout << symbol;
        }
        cout << '\n';
    }
}

void printPineTree(int n, char symbol)
{
    for (int i = 1; i <= n; i++)
    {
        printShiftedTriangle(i+1, n-i, symbol);
    }
}