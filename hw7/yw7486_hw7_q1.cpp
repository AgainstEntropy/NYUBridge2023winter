# include <iostream>
using namespace std;

int printMonthCalender(int numOfDays, int startingDay);
void printYearCalender(int year, int startingDay);
bool isLeapYear(int year);
void monthInfo(int monthInt, string &monthString, int &numOfDays, bool leapyear);

const string WEEK_TITLE = "Mon\tTue\tWed\tThu\tFri\tSat\tSun";
const char SPACE = ' ';
const int   DAYS_IN_A_WEEK = 7,
            MONTHS_IN_A_YEAR = 12;

int main()
{
    int year, starting_day;
    cout << "Please enter the year you want to print the calender: ";
    cin >> year;
    cout << "Please enter an integer reperent the day in the week of 1/1 in the year: ";
    cin >> starting_day;

    printYearCalender(year, starting_day);

    return 0;
}

int printMonthCalender(int numOfDays, int startingDay)
{
    cout << WEEK_TITLE << endl;
    for (int i = 0; i < startingDay-1; i++) cout << SPACE << '\t';
    int column;
    for (int j = 0; j < numOfDays; j++)
    {
        column = (j + startingDay) % DAYS_IN_A_WEEK;
        cout << j + 1 << '\t';
        if (column == 0) cout << endl;
    }
    
    return column;
}

void printYearCalender(int year, int startingDay)
{
    string month_string;
    int num_of_days;
    for (int m = 1; m <= MONTHS_IN_A_YEAR; m++)
    {
        monthInfo(m, month_string, num_of_days, isLeapYear(year));
        cout << endl << month_string << ' ' << year << endl;
        startingDay = printMonthCalender(num_of_days, startingDay) + 1;
        if (startingDay != 1) cout << endl;
    }
}

bool isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}

void monthInfo(int monthInt, string &monthString, int &numOfDays, bool leapyear)
{
    switch (monthInt)
    {
    case 1:
        monthString = "January";
        numOfDays = 31;
        break;
    case 2:
        monthString = "February";
        numOfDays = (leapyear ? 29 : 28);
        break;
    case 3:
        monthString = "March";
        numOfDays = 31;
        break;
    case 4:
        monthString = "April";
        numOfDays = 30;
        break;
    case 5:
        monthString = "May";
        numOfDays = 31;
        break;
    case 6:
        monthString = "June";
        numOfDays = 30;
        break;
    case 7:
        monthString = "July";
        numOfDays = 31;
        break;
    case 8:
        monthString = "August";
        numOfDays = 31;
        break;
    case 9:
        monthString = "September";
        numOfDays = 30;
        break;
    case 10:
        monthString = "October";
        numOfDays = 31;
        break;
    case 11:
        monthString = "November";
        numOfDays = 30;
        break;
    case 12:
        monthString = "December";
        numOfDays = 31;
        break;
    default:
        cout << "Invalid month!";
        exit(-1);
    }
}
