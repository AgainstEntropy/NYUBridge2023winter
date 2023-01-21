#include <iostream>
#include <string>
using namespace std;

int main()
{
    string name, status;
    int gradYear, currentYear;

    cout << "Please enter your name: ";
    cin >> name;
    cout << "Please enter your graduation year: ";
    cin >> gradYear;
    cout << "Please enter current year: ";
    cin >> currentYear;

    switch (gradYear - currentYear)
    {
    case 0:
        status = "Graduated.";
        break;
    case 1:
        status = "a Senior.";
        break;
    case 2:
        status = "a Junior.";
        break;
    case 3:
        status = "a Sophomore.";
        break;
    case 4:
        status = "a Freshman.";
        break;
    default:
        status = "not in college yet.";
    }

    cout << name << ", you are " << status << endl;

    return 0;
}
