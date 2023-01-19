#include <iostream>
using namespace std;

const int QUARTER_TO_CENT = 25,
          DIME_TO_CENT = 10,
          NICKEL_TO_CENT = 5,
          PENNIES_TO_CENT = 1;

int main()
{
    int quarters, dimes, nickels, pennies;

    cout << "Please enter number of coins :\n";
    cout << "# of quarters:";
    cin >> quarters;
    cout << "# of dimes:";
    cin >> dimes;
    cout << "# of nickels:";
    cin >> nickels;
    cout << "# of pennies:";
    cin >> pennies;

    int cents = QUARTER_TO_CENT * quarters + DIME_TO_CENT * dimes + NICKEL_TO_CENT * nickels + PENNIES_TO_CENT * pennies;
    int dollars = cents / 100;
    cents %= 100;

    cout << "The total is " << dollars << " dollars and " << cents << " cents!";
}
