#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Sorting {
public:
    virtual string worst_case_runtime() = 0;
    virtual vector<int> sort(vector<int> vec) = 0;
};


class InsertionSort : public Sorting {
public:
    virtual string worst_case_runtime() { return "O(N^2)"; }
    virtual vector<int> sort(vector<int> vec) {
        int size = vec.size();
        for (int i = 1; i < size; i++) {
            insert(vec, i);
        }
        return vec;
    }

    void insert(vector<int> &vec, int index) {
        int i, temp;
        for (i = index; i > 0; i--) {
            if (vec[i] < vec[i-1]) {
                temp = vec[i];
                vec[i] = vec[i-1];
                vec[i-1] = temp;
            } else {
                break;
            }
        }
    }
};


class QuickSort : public Sorting {
public:
    virtual string worst_case_runtime() { return "O(N^2)"; }
    virtual vector<int> sort(vector<int> vec) {
        vector<int> vec_ = vec;
        int start = 0, end = vec_.size();
        sort(vec_, start, end-1);
        return vec_;
    }

    void sort(vector<int> &vec, int start, int end) {
        if (start >= end) return;
        int pivot = vec[end];

        int left = start, 
            right = end - 1;
        while (left < right) {
            while (vec[left] < pivot && left < right) { 
                left++; 
            }
            while (vec[right] > pivot && left < right) { 
                right--; 
            }
            swap(vec[left], vec[right]);
        }
        if (vec[left] > pivot) { 
            swap(vec[end], vec[left]); 
        } else {
            left++;
        }
        
        sort(vec, start, left - 1);
        sort(vec, left + 1, end);
    }
};


class MergeSort : public Sorting {
public:
    virtual string worst_case_runtime() { return "O(Nlog(N))"; }
    virtual vector<int> sort(vector<int> vec) {
        sort(vec, 0, vec.size()-1);
        return vec;
    }

    void sort(vector<int> &vec, int start, int end) {
        if (start >= end) return;
        int mid = (start + end) / 2;
        sort(vec, start, mid);
        sort(vec, mid+1, end);
        merge(vec, start, mid, end);
    }

    void merge(vector<int> &vec, int start, int mid, int end) {
        int i = start, 
            j = mid + 1;
        vector<int> vec_;
        while (i <= mid || j <= end) {
            if ((vec[i] < vec[j] && i <= mid) || j > end) {
                vec_.push_back(vec[i++]);
            } else if (j <= end || i > mid) {
                vec_.push_back(vec[j++]);
            }
        }
        
        for (i = 0; i < vec_.size(); i++) {
            vec[start + i] = vec_[i];
        }
    }
};


int main() {
    vector<int> vec = {6, 5, 7, 4, 2, 9, 10};
    vector<int> vec1, vec2, vec3;

    // InsertionSort insertion_sort;
    // vec1 = insertion_sort.sort(vec);

    // QuickSort quicksort;
    // vec2 = quicksort.sort(vec);

    MergeSort mergesort;
    vec3 = mergesort.sort(vec);

    return 0;
}