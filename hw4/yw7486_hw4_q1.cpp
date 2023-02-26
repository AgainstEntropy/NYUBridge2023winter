#include <iostream>
using namespace std;

int main()
{
    int numEven;
    cout << "section a" << endl;
    cout << "Please enter a positive integer: ";
    cin >> numEven;

    int counter = 0;
    while (counter++ < numEven)
    {
        cout << 2 * counter << endl;
    }

    cout << "\nsection b" << endl;
    cout << "Please enter a positive integer: ";
    cin >> numEven;
    for (counter = 1; counter <= numEven; counter++)
    {
        cout << 2 * counter << endl;
    }

    return 0;
}
