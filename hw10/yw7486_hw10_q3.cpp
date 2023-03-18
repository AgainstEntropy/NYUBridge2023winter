# include <iostream>
# include <vector>
using namespace std;

void main1();
void main2();
int* initArray(int arrSize);
int* appendArray(int arr[], int& arrSize, int newNum);
void printArray(int* arr, int arrSize, string sep, string end);
void printVector(vector<int> vec, string sep, string end);

const string SPACE = " ";
const string PROMPT_1 = "Please enter a sequence of positive integers, each in a separate line.\n"
                        "End you input by typing -1.\n";
const string PROMPT_2 = "Please enter a number you want to search.\n";
const string NEGATIVE_MESSAGE = " does not show at all in the sequence.\n";

int main() {
    cout<< "section a" <<endl;
    main1();

    cout<< "section b" <<endl;
    main2();

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

    if (frequency == 0) {
        cout << to_string(search_num) + NEGATIVE_MESSAGE;
    } else {
        cout << to_string(search_num) + " shows in "
             << ((frequency == 1) ? "line " : "lines ");
        printArray(indexs, frequency, ", ", ".\n");
    }

    delete [] indexs;
    indexs = nullptr;
}

void main2() {
    cout << PROMPT_1;

    vector<int> arr;
    int new_num;
    while (true) {
        cin >> new_num;
        if (new_num == -1) break;
        arr.push_back(new_num);
    }

    cout << PROMPT_2;
    int search_num;
    cin >> search_num;

    vector<int> indexs;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == search_num) {
            indexs.push_back(i+1);
        }
    }
    if (indexs.empty()) {
        cout << to_string(search_num) + NEGATIVE_MESSAGE;
    } else {
        cout << to_string(search_num) + " shows in "
             << ((indexs.size() == 1) ? "line " : "lines ");
        printVector(indexs, ", ", ".\n");
    }
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

void printArray(int* arr, int arrSize, string sep = ", ", string end = ".") {
    string printed = "";
    for (int i = 0; i < arrSize-1; i++) {
        printed += (to_string(arr[i]) + sep);
    }
    printed += (to_string(arr[arrSize-1]) + end);
    cout << printed << endl;
}

void printVector(vector<int> vec, string sep = ", ", string end = ".") {
    string printed = "";
    for (int i = 0; i < vec.size()-1; i++) {
        printed += (to_string(vec[i]) + sep);
    }
    printed += (to_string(vec[vec.size()-1]) + end);
    cout << printed << endl;
}