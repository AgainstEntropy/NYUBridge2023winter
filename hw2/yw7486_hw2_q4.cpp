#include <iostream>
using namespace std;

int main()
{
	int numFormer, numLatter;
	cout << "Please enter two positive integers, separated by a space:\n";
	cin >> numFormer >> numLatter;

	cout << numFormer << " + " << numLatter << " = " << numFormer + numLatter << endl;
	cout << numFormer << " - " << numLatter << " = " << numFormer - numLatter << endl;
	cout << numFormer << " * " << numLatter << " = " << numFormer * numLatter << endl;
	cout << numFormer << " / " << numLatter << " = " << (float) numFormer / (float) numLatter << endl;
	cout << numFormer << " div " << numLatter << " = " << numFormer / numLatter << endl;
	cout << numFormer << " mod " << numLatter << " = " << numFormer % numLatter << endl;
}