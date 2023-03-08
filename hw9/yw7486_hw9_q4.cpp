# include <iostream>
using namespace std;

void oddsKeepEvensFlip(int arr[], int arrSize);
void printArray(int* arr, int arrSize);

const char SPACE = ' ';

int main()
{
    int arr[] = {5, 2, 11, 7, 6, 4};
    int arr_size = 6;

    oddsKeepEvensFlip(arr, arr_size);
    printArray(arr, arr_size);

    return 0;
}

void oddsKeepEvensFlip(int arr[], int arrSize)
{
    int* temp = new int[arrSize], odd_num = 0, even_num = 0;
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] % 2)
            temp[odd_num++] = arr[i];
        else
            temp[arrSize - 1 - (even_num++)] = arr[i];
    }

    for (int i = 0; i < arrSize; i++)
        arr[i] = temp[i];
    delete [] temp;
}


void printArray(int* arr, int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        cout << arr[i] << SPACE;
    }
    cout << endl;
}