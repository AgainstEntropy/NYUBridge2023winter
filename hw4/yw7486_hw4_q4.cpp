#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    cout.setf(ios::showpoint);
    cout.precision(5);

    cout << "section a" << endl;
    int lenOfSeq;
    cout << "Please enter the length of the sequence: ";
    cin >> lenOfSeq;
    cout << "Please enter your sequence:\n";

    int num;
    int product = 1;
    for (int i = 1; i <= lenOfSeq; i++)
    {
        cin >> num;
        product *= num;
    }

    cout << "The geometric mean is: " << pow(product, 1.0 / lenOfSeq) << endl;

    cout << "\nsection b" << endl;
    cout << "Please enter a non-empty sequence of positive integers, "
         << "each one in a separate line. End your sequence by typing - 1:\n";

    product = 1;
    lenOfSeq = 0;
    while (1)
    {
        cin >> num;
        if (num == -1)
        {
            break;
        }
        else
        {
            lenOfSeq++;
            product *= num;
        }
    }

    cout << "The geometric mean is: " << pow(product, 1.0 / lenOfSeq) << endl;


    return 0;
}
