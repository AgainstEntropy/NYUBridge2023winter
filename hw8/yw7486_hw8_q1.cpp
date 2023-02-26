# include <iostream>
using namespace std;

int minInArray(int arr[], int arrSize);
void printLocInArray(int arr[], int arrSize, int num);
void printArray(int arr[], int arrSize);

const int NUM_OF_INTS = 20;
const char SPACE = ' ';

int main()
{
    cout << "Please enter 20 integers separated by a space:\n";
    int arr[NUM_OF_INTS];
    for (int i = 0; i < NUM_OF_INTS; i++)
    {
        cin >> arr[i];
    }

    // printArray(arr, NUM_OF_INTS);
    int min = minInArray(arr, NUM_OF_INTS);
    cout << "The minimum value is " << min << " and it is located in the following indices: ";
    printLocInArray(arr, NUM_OF_INTS, min);

    return 0;
}

int minInArray(int arr[], int arrSize)
{
    int min = arr[0];
    for (int i = 1; i < arrSize; i++)
    {
        if (arr[i] < min) min = arr[i];
    }
    
    return min;
}

void printLocInArray(int arr[], int arrSize, int num)
{
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] == num) cout << i << SPACE;
    }
}

void printArray(int arr[], int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        cout << arr[i] << SPACE;
    }
}