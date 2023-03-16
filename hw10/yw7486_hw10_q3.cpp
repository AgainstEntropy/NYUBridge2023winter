# include <iostream>
using namespace std;

void main1();
void main2();
void printArray(int* arr, int arrSize, string sep, string end);
int* initArray(int arrSize);
int* appendArray(int arr[], int& arrSize, int newNum);

const string SPACE = " ";
const string PROMPT_1 = "Please enter a sequence of positive integers, each in a separate line.\n"
                        "End you input by typing -1.\n";
const string PROMPT_2 = "Please enter a number you want to search.\n";
const string NEGATIVE_MESSAGE = " does not show at all in the sequence.";

int main() {
    main1();

    // main2();

    return 0;
}

void main1() {
    cout << PROMPT_1;
    int arr_size = 1;
    int* arr = initArray(arr_size);

    int new_num;
    while (true) {
        cin >> new_num;
        if (new_num == -1) break;
        arr = appendArray(arr, arr_size, new_num);
    }

    cout << PROMPT_2;
    int search_num, frequency = 0;
    cin >> search_num;

    int* indexs = initArray(frequency);
    for (int i = 1; i < arr_size; i++)
    {
        if (arr[i] == search_num) {
            indexs = appendArray(indexs, frequency, i);
        }
    }
    cout << to_string(search_num) + " shows in lines ";
    printArray(indexs, frequency, ", ", ".");
}

void main2() {
    cout << PROMPT_1;
}

void printArray(int* arr, int arrSize, string sep = ", ", string end = ".") {
    string printed = "";
    for (int i = 0; i < arrSize-1; i++) {
        printed += (to_string(arr[i]) + sep);
    }
    printed += (to_string(arr[arrSize-1]) + end);
    cout << printed << endl;
}

int* initArray(int arrSize) {
    int* arr = new int[arrSize];
    for (int i = 0; i < arrSize; i++) {
        arr[i] = 0;
    }
    return arr;
}

int* appendArray(int arr[], int& arrSize, int newNum) {
    int* new_arr = new int[arrSize+1];
    for (int i = 0; i < arrSize; i++) {
        new_arr[i] = arr[i];
    }
    delete [] arr;
    new_arr[arrSize] = newNum;
    arrSize++;
    return new_arr;
}