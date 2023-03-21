# include <iostream>
# include <cmath>
using namespace std;

int sumOfSquares(int arr[], int arrSize);
bool isSorted(int arr[], int arrSize);

int main() {
    int arr[4] = {1, 2, 3, 4};
    int arr_size = 4;

    cout << "The sum of the squares of the array is "
         << sumOfSquares(arr, arr_size) << endl;

    if (isSorted(arr, arr_size)) {
        cout << "The array is sorted in an ascending order.";
    } else {
        cout << "The array is not sorted in an ascending order.";
    }

    return 0;
}

int sumOfSquares(int arr[], int arrSize) {
    int sum = (arrSize == 1) ? 0 : sumOfSquares(arr, arrSize-1);
    return sum + pow(arr[arrSize-1], 2);
}

bool isSorted(int arr[], int arrSize) {
    if (arrSize == 1) {
        return true;
    } else {
        return (arr[arrSize-1] >= arr[arrSize-2]) ? isSorted(arr, arrSize-1) : false;
    }
}
