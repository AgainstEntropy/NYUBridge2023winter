#include <iostream>
#include <queue>

using namespace std;

template <class T>
class Stack {
    queue<T> data;
    T top_val;
public:
    Stack() {}

    T top() const { return top_val; }
    void push(T newItem) { data.push(newItem); top_val = newItem; }
    void pop();
    int size() { return data.size(); }
};

template <class T>
void Stack<T>::pop() {
    queue<T> newdata;
    int newsize = data.size()-1;
    for (int i = 0; i < newsize; i++) {
        newdata.push(data.front());
        data.pop();
    }
    data.pop();

    for (int i = 0; i < newsize; i++) {
        this->push(newdata.front());
        newdata.pop();
    }
}


int main() {
    
    Stack<int> stack;
    for (int i = 0; i < 5; i++) {
        stack.push(i);
    }

    cout << stack.top() << endl;

    cout << stack.size() << endl;
    for (int i = 0; i < 2; i++) {
        stack.pop();
    }
    
    cout << stack.top() << endl;
    
    return 0;
}