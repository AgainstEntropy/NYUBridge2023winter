#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Money
{
public:
    friend Money operator+(const Money &amount1, const Money &amount2);
    friend Money operator-(const Money &amount1, const Money &amount2);
    friend Money operator-(const Money &amount);
    friend bool operator==(const Money &amount1, const Money &amount2);
    friend bool operator<(const Money &amount1, const Money &amount2);
    Money(long dollars, int cents);
    Money(long dollars) : all_cents(dollars * 100) {}
    Money(double amount);
    Money() : all_cents(0) {}
    // double get_value();
    double get_value( ) const { return (all_cents * 0.01); }

    friend istream &operator>>(istream &ins, Money &amount);
    friend ostream &operator<<(ostream &outs, const Money &amount);

private:
    long all_cents;
};

Money::Money(long dollars, int cents)
{
    if (dollars * cents < 0) // If one is negative and one is positive
    {
        cout << "Illegal values for dollars and cents.\n";
        exit(1);
    }
    all_cents = dollars * 100 + cents;
}

Money::Money(double amount)
{
    long dollars = static_cast<long>(amount);
    int cents = static_cast<int>(round((amount - dollars) * 100));
    all_cents = dollars * 100 + cents;
}

Money operator+(const Money &amount1, const Money &amount2)
{
    Money temp;
    temp.all_cents = amount1.all_cents + amount2.all_cents;
    return temp;
}

Money operator-(const Money &amount1, const Money &amount2)
{
    Money temp;
    temp.all_cents = amount1.all_cents - amount2.all_cents;
    return temp;
}

Money operator-(const Money &amount)
{
    Money temp;
    temp.all_cents = -amount.all_cents;
    return temp;
}

bool operator==(const Money &amount1, const Money &amount2)
{
    return (amount1.all_cents == amount2.all_cents);
}

bool operator<(const Money &amount1, const Money &amount2)
{
    return (amount1.all_cents < amount2.all_cents);
}

int digit_to_int(char c)
{
    return (static_cast<int>(c) - static_cast<int>('0'));
}

// Uses iostream, cctype, cstdlib:
istream &operator>>(istream &ins, Money &amount)
{
    char one_char, decimal_point,
        digit1, digit2; // digits for the amount of cents
    long dollars;
    int cents;
    bool negative; // set to true if input is negative.
    ins >> one_char;
    if (one_char == '-')
    {
        negative = true;
        ins >> one_char; // read '$'
    }
    else
        negative = false;
    // if input is legal, then one_char == '$'
    ins >> dollars >> decimal_point >> digit1 >> digit2;
    if (one_char != '$' || decimal_point != '.' || !isdigit(digit1) || !isdigit(digit2))
    {
        cout << "Error illegal form for money input\n";
        exit(1);
    }
    cents = digit_to_int(digit1) * 10 + digit_to_int(digit2);
    amount.all_cents = dollars * 100 + cents;
    if (negative)
        amount.all_cents = -amount.all_cents;
    return ins;
}

// Uses cstdlib and iostream:
ostream &operator<<(ostream &outs, const Money &amount)
{
    long positive_cents, dollars, cents;
    positive_cents = labs(amount.all_cents);
    dollars = positive_cents / 100;
    cents = positive_cents % 100;

    if (amount.all_cents < 0)
        outs << "- $" << dollars << '.';
    else
        outs << "$" << dollars << '.';

    if (cents < 10)
        outs << '0';
    outs << cents;

    return outs;
}

class Check
{
public:
    Check(int num, double amount, bool cashed);
    int get_num() { return Num; }
    Money get_amount() { return Amount; }
    bool is_cashed() { return Cashed; }

    friend ostream &operator<<(ostream &outs, Check &c);

private:
    int Num;      // the number of each check (int)
    Money Amount; // the amount of the check (double)
    bool Cashed;  // whether or not it has been cashed (1 or 0, boolean in the array).
};

Check::Check(int num, double amount, bool cashed) : Num(num), Amount(amount), Cashed(cashed)
{
    if (amount < 0)
    {
        cout << "Illegal values for amount.\n";
        exit(1);
    }
}

ostream &operator<<(ostream &outs, Check &c)
{
    // outs << c.Num << '\t' << c.Amount << '\t' << (c.Cashed ? "Cashed" : "Not cashed");
    outs << "Check number: " << c.Num << " with amount: " << c.Amount;
    return outs;
}

void getCheckList(vector<Check>& cashedCheckList, vector<Check>& uncashedCheckList) {
    int number; double amount; bool cashed;
    while ((cin >> number >> amount >> cashed) && !(number == 0 && amount == 0.0 && cashed == 0)) {
        (cashed ? cashedCheckList : uncashedCheckList).push_back(Check(number, amount, amount));
    }
}

Money sumChecks(vector<Check> checkList) {
    Money temp;
    for (Check c:checkList) {
        temp = temp + c.get_amount();
    }
    return temp;
}

Money getDeposits() {
    double total_deposit = 0, deposit;
    while ((cin >> deposit) && (deposit != 0)) {
        total_deposit += deposit;
    }
    return Money(total_deposit);
}

bool compareCheck(Check c1, Check c2) {
    return (c1.get_num() < c2.get_num());
}

int main()
{
    cout << "please enter the check number, amount on check [exclude the dollar signl and whether or not the check has been\n"
         << "cashed(by typing 1(Yes) or 0(No):\n\n"
         << "Example input: 9 for check number, 40.89 for amount and 1 for being cashed (9 40.89 1)\n"
         << "End output by entering  for check number, 0.00 for amount and 0 for being cashed (0 0.00 0)\n\n";
    
    vector<Check> cashed_checks, uncashed_checks;
    getCheckList(cashed_checks, uncashed_checks);
    
    Money sum_of_cashed_checks = sumChecks(cashed_checks), 
          sum_of_uncashed_checks = sumChecks(uncashed_checks);
    cout << "The sum of the cashed checks is:\n"
         << sum_of_cashed_checks << endl
         << "The sum of the un-cashed checks is:\n"
         << sum_of_uncashed_checks << endl;

    cout << "Please enter the deposits (end deposit input by typing 0):\n";
    Money total_deposit = getDeposits();
    cout << "The sum of the deposits is:\n"
         << total_deposit << endl;

    double prior_balance_amount, new_balance_amount;
    cout << "Please enter the prior balance amount:\n";
    cin >> prior_balance_amount;
    Money prior_balance(prior_balance_amount);
    Money balance = prior_balance_amount + total_deposit - sum_of_cashed_checks;

    cout << "Please enter the new balance amount according to account holder:\n";
    cin >> new_balance_amount;
    Money new_balance(new_balance_amount);

    cout << "\nThe balance according to the bank which includes only cleared checks is: " << balance << endl
         << "The difference between the account holders balance of " << new_balance 
         << " and bank balance of " << balance << " is: " << balance - new_balance << endl;

    cout << "\nThe cashed checks are:\n";
    sort(cashed_checks.begin(), cashed_checks.end(), compareCheck);
    for (Check c:cashed_checks) {
        cout << c << endl;
    }

    cout << "\nThe un-cashed checks are:\n";
    sort(uncashed_checks.begin(), uncashed_checks.end(), compareCheck);
    for (Check c:uncashed_checks) {
        cout << c << endl;
    }
    
    return 0;
}