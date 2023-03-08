# include <iostream>
using namespace std;

int* getPosNums1(int* arr, int arrSize, int& outPosArrSize);
int* getPosNums2(int* arr, int arrSize, int* outPosArrSizePtr);
void getPosNums3(int* arr, int arrSize, int*& outPosArr, int& outPosArrSize);
void getPosNums4(int* arr, int arrSize, int** outPosArrPtr, int* outPosArrSizePtr);
void printArray(int* arr, int arrSize);

const char SPACE = ' ';

int main()
{
    int arr[] = {3, -1, -3, 0, 6, 4};
    int arr_size = 6;

    int arr_size1;
    int* arr1 = getPosNums1(arr, arr_size, arr_size1);
    printArray(arr1, arr_size1);

    int arr_size2;
    int* arr2 = getPosNums2(arr, arr_size, &arr_size2);
    printArray(arr2, arr_size2);

    int* arr3 = new int[arr_size];
    int arr_size3;
    getPosNums3(arr, arr_size, arr3, arr_size3);
    printArray(arr3, arr_size3);

    int *arr4, arr_size4;
    getPosNums4(arr, arr_size, &arr4, &arr_size4);
    printArray(arr4, arr_size4);

    return 0;
}

int* getPosNums1(int* arr, int arrSize, int& outPosArrSize)
{
    int* temp = new int[arrSize];
    outPosArrSize = 0;
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] > 0)
            temp[outPosArrSize++] = arr[i];
    }

    return temp;
}

int* getPosNums2(int* arr, int arrSize, int* outPosArrSizePtr)
{
    int* temp = new int[arrSize];
    *outPosArrSizePtr = 0;
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] > 0)
            temp[(*outPosArrSizePtr)++] = arr[i];
    }

    return temp;
}

void getPosNums3(int* arr, int arrSize, int*& outPosArr, int& outPosArrSize)
{
    outPosArrSize = 0;
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] > 0)
            outPosArr[outPosArrSize++] = arr[i];
    }
}

void getPosNums4(int* arr, int arrSize, int** outPosArrPtr, int* outPosArrSizePtr)
{
    int* temp = new int[arrSize];
    *outPosArrSizePtr = 0;
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] > 0)
            temp[(*outPosArrSizePtr)++] = arr[i];
    }
    *outPosArrPtr = temp;
}


void printArray(int* arr, int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        cout << arr[i] << SPACE;
    }
    cout << endl;
}