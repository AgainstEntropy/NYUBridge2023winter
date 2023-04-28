#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void openInputFile(ifstream& inFile) {
	cout << "Enter the filename: ";
    string file_name;
    getline(cin, file_name);
	inFile.open(file_name);
	while (!inFile) {
		cout << "FILE FAILED TO OPEN! " << endl;
		cout << "What filename? ";
		cin >> file_name;
		inFile.clear();
		inFile.open(file_name);
	}
}


struct Person {
    Person() : paid(-1), name("someone"), owed(-1) {}
    Person(double paid, string name) : paid(paid), name(name), owed(0) {}

    double paid, owed;
    string name; 
};


template <class T>
class LList; //Pre-Definition to make Friend work in LListNode

template <class T>
class LListNode {
	T data;
	LListNode<T>* next;
	LListNode<T>* prev;
public:
	LListNode(const T& newdata = T(), LListNode<T>* newnext = nullptr, LListNode<T>* newprev = nullptr) :data(newdata), next(newnext), prev(newprev) {}
	friend class LList<T>;
};

template <class T>
class LList {
	LListNode<T>* head;
	LListNode<T>* tail;
	
public:
	LList();
	~LList();
	LList(const LList<T>& rhs);
	LList<T>& operator=(const LList<T>& rhs);

	void clear() { while (!isEmpty()) pop_front(); }
	void push_back(const T& data) { tail->prev = new LListNode<T>(data, tail, tail->prev); tail->prev->prev->next = tail->prev; }
	void push_front(const T& data) { head->next = new LListNode<T>(data, head->next, head);  head->next->next->prev = head->next; }
	T pop_back();
	T pop_front();
	int size() const;
	bool isEmpty() const { return head->next == tail; }

    void printInfo(bool paid);
    double calcOwed();
    bool isBillClear() const;
    void pay();
    void splitBill();
};

template <class T>
LList<T>& LList<T>::operator=(const LList<T>& rhs) {
	if (this == &rhs)
		return *this;
	clear();
	LListNode<T>* ptr = rhs.head->next;
	while (ptr != rhs.tail) {
		push_back(ptr->data);
	}
	return *this;
}

template <class T>
int LList<T>::size() const {
	LListNode<T>* ptr = head->next;
	int count = 0;
	while (ptr != tail) {
		count++;
		ptr = ptr->next;
	}
	return count;
}

template <class T>
T LList<T>::pop_back() {
	if (tail->prev == head) //empty list!
		return T(); //not sure what to do here?  User did something dumb.
	T retval = tail->prev->data;
	LListNode<T>* nodeToDelete = tail->prev;
	tail->prev = nodeToDelete->prev;
	nodeToDelete->prev->next = nodeToDelete->next;
	delete nodeToDelete;
	return retval;
}

template <class T>
T LList<T>::pop_front() {
	if (tail->prev == head) //empty list!
		return T(); //not sure what to do here?  User did something dumb.
	T retval = head->next->data;
	LListNode<T>* nodeToDelete = head->next;
	head->next = nodeToDelete->next;
	head->next->prev = head;
	delete nodeToDelete;
	return retval;
}

template <class T>
LList<T>::~LList() {
	clear();
	delete head;
	delete tail;
}

template <class T>
LList<T>::LList(const LList<T>& rhs) {
	head = new LListNode<T>();
	tail = new LListNode<T>();
	head->next = tail;
	tail->prev = head;
	*this = rhs; //call to the assignment operator!!!
}

template <class T>
LList<T>::LList() { //build two nodes, as "Dummies" for teh sake of making things easier
	head = new LListNode<T>();
	tail = new LListNode<T>();
	head->next = tail;
	tail->prev = head;
}

template <class T>
void LList<T>::printInfo(bool paid) {
	LListNode<T>* ptr = head->next;
	while (ptr != tail) {
        // Person p = ptr->data;
        T p = ptr->data;
        if (paid) {
            cout << p.name << '\t' << p.paid << '\t' << p.owed << '\n';
        } else {
            cout << p.name << '\t' << p.owed << '\n';
        }
		ptr = ptr->next;
	}
}

template <class T>
double LList<T>::calcOwed() {
    double sum = 0, avg;
	LListNode<T>* ptr = head->next;
	while (ptr != tail) {
        T p = ptr->data;
		sum += p.paid;
		ptr = ptr->next;
	}

    avg = sum / size();
    ptr = head->next;
	while (ptr != tail) {
        T* p = &(ptr->data);
		p->owed = avg - p->paid;
		ptr = ptr->next;
	}

    return avg;
}

template <class T>
bool LList<T>::isBillClear() const {
	LListNode<T>* ptr = head->next;
	while (ptr != tail) {
        T p = ptr->data;
		if (abs(p.owed) > 1e-6) {
            return false;
        }
		ptr = ptr->next;
	}

    return true;
}

template <class T>
void LList<T>::pay() {
	LListNode<T>* ptr = head->next;
    T *p_owe = nullptr, *p_accept = nullptr;
    // find someone to pay and someone to accept
	while ((!p_owe || !p_accept) && ptr != tail) {
        T* p = &(ptr->data);
		if (!p_owe && p->owed > 0) {  // pay
            p_owe = p;
        } else if (!p_accept && p->owed < 0) {  //accept
            p_accept = p;
        }
		ptr = ptr->next;
	}

    cout << p_owe->name << ", you give " << p_accept->name << " $";
    if (p_owe->owed + p_accept->owed > 0) {
        cout << -p_accept->owed << "\n";
        p_owe->owed += p_accept->owed;
        p_accept->owed -= p_accept->owed;
    } else {
        cout << p_owe->owed << "\n";
        p_accept->owed += p_owe->owed;
        p_owe->owed -= p_owe->owed;
    }
}

template <class T>
void LList<T>::splitBill() {
	LListNode<T>* ptr = head->next;
	while (ptr != tail) {
        T p = ptr->data;
		if (p.owed == 0) {
            cout << p.name << ", you don't need to do anything\n";
        }
		ptr = ptr->next;
	}

    while (!isBillClear()) {
        pay();
    }
}


int main() {
    ifstream inFile;
    openInputFile(inFile);

    LList<Person> persons;

    double paid;
    string name;
    while (inFile >> paid) {
        inFile.ignore(9999, '\t');
        getline(inFile, name);
        persons.push_back(Person(paid, name));
    }

    double avg = persons.calcOwed();
    // persons.printInfo(true);

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(6);
    persons.splitBill();

    cout.precision(2);
    cout << "In the end, you should all have spent around $" << avg;

    return 0;
}
