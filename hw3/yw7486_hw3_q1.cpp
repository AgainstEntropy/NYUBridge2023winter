#include <iostream>
using namespace std;

int main()
{
    double price1, price2, taxRate;
    char haveClubCard;

    cout << "Enter price of first item: ";
    cin >> price1;
    cout << "Enter price of second item: ";
    cin >> price2;
    cout << "Does customer have a club card ? (Y / N): ";
    cin >> haveClubCard;
    cout << "Enter tax rate, e.g. 5.5 for 5.5% tax: ";
    cin >> taxRate;

    cout.precision(10);

    double basePrice = price1 + price2;
    cout << "Base price : " << basePrice << endl;

    double priceAfterDiscounts = 
        (price1 < price2) ? price1 * 0.5 + price2 : price1 + price2 * 0.5;
    if (haveClubCard == 'y' || haveClubCard == 'Y')
    {
        priceAfterDiscounts *= 0.9;
    }
    cout << "Price after discounts : " << priceAfterDiscounts << endl;

    double totalPrice = priceAfterDiscounts * (1 + taxRate / 100);
    cout << "Total price : " << totalPrice << endl;

    return 0;
}
