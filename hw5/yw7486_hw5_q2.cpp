#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_GUESS_TIMES = 5;

int main()
{
	srand(time(0));
	int randNum = (rand() % 100) + 1;
	
	cout << "I thought of a number between 1 and 100!Try to guess it.\n";

	int lowerBound = 1,
		upperBound = 100;

	int guessNum;

	for (int i = 0; i < MAX_GUESS_TIMES; i++)
	{
		cout << "Range: [" << lowerBound << ',' << upperBound << "], Number of guesses left : "
			 << MAX_GUESS_TIMES - i << endl << "Your guess: ";
		cin >> guessNum;

		if (guessNum == randNum)
		{
			cout << "Congrats! You guessed my number in " << i + 1 << " guesses.";
			break;
		}
		else if (i == MAX_GUESS_TIMES - 1)
		{
			cout << "Out of guesses! My number is " << randNum;
		}
		else if (guessNum < randNum)
		{
			cout << "Wrong! My number is bigger.\n\n";
			lowerBound = guessNum;
		}
		else
		{
			cout << "Wrong! My number is smaller.\n\n";
			upperBound = guessNum;
		}
	}
	
	return 0;
}