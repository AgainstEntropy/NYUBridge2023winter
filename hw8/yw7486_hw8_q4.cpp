# include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void genRandMapping(int array[], int arrSize);
bool checkPin(int pin, int actualPin, int map[]);
void printArray(int arr[], int arrSize);

const char SPACE = ' ';
const int   NUM_OF_DIGITS = 10,
            ACTUAL_PIN = 12345;

int main()
{
    int map[NUM_OF_DIGITS];
    genRandMapping(map, NUM_OF_DIGITS);
    cout    << "Please enter your PIN according to the following mapping:\n"
            << "PIN: \t0 1 2 3 4 5 6 7 8 9\n"
            << "NUM: \t";
    printArray(map, NUM_OF_DIGITS);
    int pin;
    cin >> pin;

    if (checkPin(pin, ACTUAL_PIN, map))
        cout << "Your PIN is correct";
    else
        cout << "Your PIN is not correct";

    return 0;
}

void genRandMapping(int array[], int arrSize)
{
    srand(time(0));
	for (int i = 0; i < arrSize; i++)
        array[i] = (rand() % 3) + 1;
}

bool checkPin(int pin, int actualPin, int map[])
{
    while (pin != 0)
    {
        if ((pin % 10) != map[actualPin % 10]) return false;
        
        pin /= 10;
        actualPin /= 10;
    }
    return true;
}

void printArray(int arr[], int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        cout << arr[i] << SPACE;
    }
    cout << endl;
}
