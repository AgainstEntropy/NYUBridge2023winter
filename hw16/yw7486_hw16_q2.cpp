#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<class T>
class Queue
{
	vector<T> data;
	int start;
	
public:
	Queue() : start(0) {};
	~Queue() {};

	void push(T newdata) { data.push_back(newdata); }
	T pop();
	int size() { return data.size(); }
	int get_start() { return start; }
};

template<class T>
T Queue<T>::pop() {
	T temp = data[start++];
	if (start == data.size()) {
		data.clear();
		start = 0;
	}
	return temp;
}


int main() {
	Queue<int> queue;
	for (int i = 0; i < 5; i++) {
		queue.push(i);
	}
	
	for (int i = 0; i < 5; i++) {
		cout << queue.pop() << "\t(size: " << queue.size() << "  start: " << queue.get_start() << ")\n";
	}

    return 0;
}
