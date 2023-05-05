#include <iostream>
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

	void enqueue(T newdata) { data.push_back(newdata); }
	T dequeue();
	int size() { return data.size() - start; }
	int get_start() { return start; }
};

template<class T>
T Queue<T>::dequeue() {
	if (data.empty()) {
		cout << "Queue is empty!" << endl;
		return -1;
	}
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
		queue.enqueue(i);
	}
	
	for (int i = 0; i < 6; i++) {
		cout << queue.dequeue() << "\t(size: " << queue.size() << "  start: " << queue.get_start() << ")\n";
	}

    return 0;
}
