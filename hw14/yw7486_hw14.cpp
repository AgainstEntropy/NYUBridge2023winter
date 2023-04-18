#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void printVector(vector<int> vec, string sep = ", ", string end = "") {
    string printed = "";
    for (int i = 0; i < vec.size()-1; i++) {
        printed += (to_string(vec[i]) + sep);
    }
    printed += (to_string(vec[vec.size()-1]) + end);
    cout << printed << endl;
}

vector<int> findMinMax(vector<int>& v, int begin, int end) {
    int min, max;

    if (begin == end) {
        min = v[begin];
        max = v[end];
    } else {
        int middle = begin + (end - begin) / 2;
        vector<int> min_max_1 = findMinMax(v, begin, middle);
        vector<int> min_max_2 = findMinMax(v, middle + 1, end);

        min = (min_max_1[0] < min_max_2[0]) ? min_max_1[0] : min_max_2[0];
        max = (min_max_1[1] > min_max_2[1]) ? min_max_1[1] : min_max_2[1];
    }
    vector<int> min_max = {min, max};
    return min_max;
}

void randInit(vector<int>& v, int length) {
    srand(time(0));
    for (int i = 0; i < length; i++)
        v.push_back(rand() % (2 * length));
}


int main() {
    vector<int> ori_vec;
    randInit(ori_vec, 9);
    printVector(ori_vec);

    vector<int> min_max = findMinMax(ori_vec, 0, ori_vec.size()-1);
    printVector(min_max);

    return 0;
}

