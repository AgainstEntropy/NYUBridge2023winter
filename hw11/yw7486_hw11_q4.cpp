# include <iostream>
using namespace std;

int minCost(int arr[], int arrSize);

int main() {
    int arr[6] = {0, 3, 80, 6, 57, 10};
    int arr_size = 6;

    cout << "The lowest cost is " << minCost(arr, arr_size);

    return 0;
}

int minCost(int arr[], int arrSize) {
    if (arrSize <= 2) {
        return arr[arrSize - 1];
    } else {
        int min1 = minCost(arr, arrSize - 1) + arr[arrSize - 1];
        int min2 = minCost(arr, arrSize - 2) + arr[arrSize - 1];
        return (min1 < min2) ? min1 : min2;
    }
}