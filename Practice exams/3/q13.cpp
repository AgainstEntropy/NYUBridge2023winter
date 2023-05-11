#include <iostream>
#include <stack>

using namespace std;

class MinStack {
private:
    stack<int> data;
    int min;
public:
    /** initialize your data structure here. */
    MinStack(): min(-1) { }
    void push(int x) {
        // Check if the stack is empty or not
        if (data.empty() || x < min) { 
            min = x; 
        }
        data.push(x);
    }

    void pop() {
        data.pop();
    }

    int top() {
        return data.top();
    }

    int getMin() {
        return min;
    }
};


int main() {
    MinStack obj = MinStack();

    for (int i = 0; i < 5; i++) {
        obj.push(i);
    }
    
    obj.pop();
    int param_3 = obj.top();
    int param_4 = obj.getMin();
            
    return 0;
}