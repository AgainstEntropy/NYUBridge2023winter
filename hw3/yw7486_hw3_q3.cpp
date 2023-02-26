#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double a, b, c;

    cout << "Please enter value of a: ";
    cin >> a;
    cout << "Please enter value of b: ";
    cin >> b;
    cout << "Please enter value of c: ";
    cin >> c;

    //cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    if (a == 0)
    {
        if (b == 0)
        {
            if (c == 0)
            {
                cout << "This equation has infinite number of solutions";
            }
            else
            {
                cout << "This equation has no solution";
            }
        }
        else // a=0, b!=0
        {
            double solution = -c / b;
            cout << "This equation has a single real solution x = " << solution << endl;
        }
    }
    else // a!=0
    {
        double delta = pow(b, 2) - 4 * a * c;
        if (delta < 0)
        {
            cout << "This equation has no real solution";
        }
        else if (delta == 0)
        {
            double solution = -b / (2 * a);
            cout << "This equation has a single real solution x = " << solution << endl;
        }
        else if (delta > 0)
        {
            double solution1 = (-b - sqrt(delta)) / (2 * a),
                   solution2 = (-b + sqrt(delta)) / (2 * a);
            cout    << "This equation has two real solutions,"
                    << " x1 = " << solution1 << ','
                    << " x2 = " << solution2 << endl;
        }
    }

    return 0;
}
