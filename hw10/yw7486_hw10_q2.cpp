# include <iostream>
using namespace std;

int* findMissing(int arr[], int n, int& resArrSize);
int sumArray(int* arr, int arrSize);
void printArray(int* arr, int arrSize);

const char SPACE = ' ';

int main() {
    int arr[] = {3, 1, 3, 0, 6, 4};

    int res_arr_size;
    int* missing_arr = findMissing(arr, 6, res_arr_size);

    string be = ((res_arr_size == 1) ? " is " : " are ");
    string noun = ((res_arr_size == 1) ? " number " : " numbers ");
    cout << "There" << be << res_arr_size << noun << "missing, which" << be << ": ";
    printArray(missing_arr, res_arr_size);

    delete [] missing_arr;
    missing_arr = nullptr;

    return 0;
}

int* findMissing(int arr[], int n, int& resArrSize) {
    int* flag_arr = new int[n+1];
    for (int i = 0; i < n+1; i++) {
        flag_arr[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        flag_arr[arr[i]] = 0;
    }
    resArrSize = sumArray(flag_arr, n+1);

    int* miss_arr = new int[resArrSize];
    int miss_index = 0;
    for (int i = 0; i < n+1; i++) {
        if (flag_arr[i]) {
            miss_arr[miss_index] = i;
            miss_index++;
        }
        if (miss_index == resArrSize) {
            delete [] flag_arr;
            flag_arr = nullptr;
            break;
        }
    }

    return miss_arr;
}

int sumArray(int* arr, int arrSize) {
    int sum = 0;
    for (int i = 0; i < arrSize; i++) {
        sum += arr[i];
    }

    return sum;
}

void printArray(int* arr, int arrSize) {
    for (int i = 0; i < arrSize; i++) {
        cout << arr[i] << SPACE;
    }
    cout << endl;
}