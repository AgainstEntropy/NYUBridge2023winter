#include <iostream>
#include <string>
using namespace std;

const int   HOUR_TO_DAY = 24,
            MINUTE_TO_HOUR = 60;

const string PREFIX = "Please enter the number of ";
const string SUFFIX_JOHN = " John has worked : ";
const string SUFFIX_BILL = " Bill has worked : ";

int main()
{
    int daysOfJohn, hoursOfJohn, minutesOfJohn;
    int daysOfBill, hoursOfBill, minutesOfBill;
    int days, hours, minutes;
    int daysCarry, hoursCarry;

    cout << PREFIX << "days" << SUFFIX_JOHN;
    cin >> daysOfJohn;
    cout << PREFIX << "hours" << SUFFIX_JOHN;
    cin >> hoursOfJohn;
    cout << PREFIX << "minutes" << SUFFIX_JOHN;
    cin >> minutesOfJohn;
    cout << PREFIX << "days" << SUFFIX_BILL;
    cin >> daysOfBill;
    cout << PREFIX << "hours" << SUFFIX_BILL;
    cin >> hoursOfBill;
    cout << PREFIX << "minutes" << SUFFIX_BILL;
    cin >> minutesOfBill;

    minutes = minutesOfJohn + minutesOfBill;
    hoursCarry = minutes / MINUTE_TO_HOUR;
    minutes %= MINUTE_TO_HOUR;

    hours = hoursOfJohn + hoursOfBill + hoursCarry;
    daysCarry = hours / HOUR_TO_DAY;
    hours %= HOUR_TO_DAY;

    days = daysOfJohn + daysOfBill + daysCarry;

    cout 
        << "The total time both of them worked together is : "
        << days << " days, "
        << hours << " hours, and "
        << minutes << " minutes.";
}
