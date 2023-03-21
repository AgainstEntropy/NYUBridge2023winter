# include <iostream>
using namespace std;

void printTriangle(int n);
void printInversedTriangle(int n);
void printOpositeTriangles(int n);
void printRuler(int n);
void printChar(int n, char Char);

const char ASTERISK = '*';
const char RULE = '-';

int main() {
    printTriangle(4);
    cout << endl;
    printOpositeTriangles(4);
    cout << endl;
    printRuler(4);

    return 0;
}

void printTriangle(int n) {
    if (n == 1) {
        printChar(1, ASTERISK);
    } else {
        printTriangle(n-1);
        printChar(n, ASTERISK);
    }
}

void printInversedTriangle(int n) {
    if (n == 1) {
        printChar(1, ASTERISK);
    } else {
        printChar(n, ASTERISK);
        printInversedTriangle(n-1);
    }
}

void printOpositeTriangles(int n) {
    printInversedTriangle(n);
    printTriangle(n);
}

void printRuler(int n) {
    if (n == 1) {
        printChar(1, RULE);
    } else {
        printRuler(n-1);
        printChar(n, RULE);
        printRuler(n-1);
    }
}

void printChar(int n, char Char) {
    for (int i = 0; i < n; i++) {
        cout << Char;
    }
    cout << endl;
}