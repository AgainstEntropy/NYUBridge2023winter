#include <iostream>
#include <cmath>
using namespace std;

const double KILOGRAM_PER_POUND = 0.453592;
const double METER_PER_INCH = 0.0254;

int main()
{
    double weight, height;

    cout << "Please enter weight(in pounds): ";
    cin >> weight;
    cout << "Please enter height(in inches): ";
    cin >> height;

    string status;
    double bmi = (weight * KILOGRAM_PER_POUND) / pow(height * METER_PER_INCH, 2);
    //cout << bmi << endl;
    if (bmi < 18.5)
    {
        status = "Underweight";
    }
    else if (bmi < 25)
    {
        status = "Normal";
    }
    else if (bmi < 30)
    {
        status = "Overweight";
    }
    else
    {
        status = "Obese";
    }

    cout << "The weight status is: " << status << endl;

    return 0;
}
