#include <iostream>
using namespace std;

const double BILL1 = 0.4,
             BILL2 = 0.25,
             BILL3 = 0.15;

int main()
{
    string day;
    int numOfMinutes, hour;
    double minute;
    char sep;

    cout << "Please enter the day of the week on which the call was made: ";
    cin >> day;
    cout << "Please enter what time the call starts: ";
    cin >> hour >> sep >> minute;
    cout << "Please enter the duration of the call: ";
    cin >> numOfMinutes;

    // cout << timeString << endl;

    double cost;
    if ((day == "Sa") || (day == "Su"))
    {
        cost = numOfMinutes * BILL3;
    }
    else
    {
        double time = hour + minute / 60.0;
        
        cost = numOfMinutes * (((time < 8) || (time > 18)) ? BILL2 : BILL3);
    }

    cout << "The cost is: $" << cost << endl;

    return 0;
}
