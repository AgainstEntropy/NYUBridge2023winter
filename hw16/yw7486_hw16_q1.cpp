#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void openInputFile(ifstream& inFile) {
	cout << "Enter the filename: ";
    string file_name;
    getline(cin, file_name);
	inFile.open(file_name);
	while (!inFile) {
		cout << "FILE FAILED TO OPEN! " << endl;
		cout << "Re-enter the filename: ";
		cin >> file_name;
		inFile.clear();
		inFile.open(file_name);
	}
}

char findLeft(char c) {
	switch (c) {
	case ')':
		return '(';
	case ']':
		return '[';
	case '}':
		return '{';
	default:
		return c;
	}
}

bool checkSymbolBalance(ifstream& inFile) {
	vector<char> symbols;
	string line;
    while (getline(inFile, line)) {
		for (char c:line) {
			if (c == '(' || c == '[' || c == '{') {
				symbols.push_back(c);
			} else if (c == ')' || c == ']' || c == '}') {
				if (findLeft(c) == symbols[symbols.size() - 1]) {
					symbols.pop_back();
				} else {
					return false;
				}
			}
		}
    }
	return true;
}

int main() {
	ifstream inFile;
    openInputFile(inFile);

	if (checkSymbolBalance(inFile)) {
		cout << "True" << endl;
	} else {
		cout << "False" << endl;
	}

    return 0;
}
