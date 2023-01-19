#include <iostream>
using namespace std;

const int   DOLLAR_TO_CENT = 100,
            QUARTER_TO_CENT = 25,
            DIME_TO_CENT = 10,
            NICKEL_TO_CENT = 5;

int main()
{
    int dollars, cents;

    cout << "Please enter your amount in the format of dollars and cents separated by a space:\n";
    cin >> dollars >> cents;
    cout << dollars << " dollars and " << cents << " cents are:\n";
    
    cents += DOLLAR_TO_CENT * dollars;
    int quarters = cents / QUARTER_TO_CENT;
    cents %= QUARTER_TO_CENT;
    int dimes = cents / DIME_TO_CENT;
    cents %= DIME_TO_CENT;
    int nickels = cents / NICKEL_TO_CENT;
    int pennies = cents % NICKEL_TO_CENT;

    cout << quarters << " quarters, " << dimes << " dimes, " << nickels << " nickels and " << pennies << " pennies";
}

