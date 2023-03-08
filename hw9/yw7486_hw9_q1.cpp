# include <iostream>
using namespace std;

int alphabetToIndex(char character);

const char SPACE = ' ';
const int NUM_OF_ALPHABETS = 26;
const int DEFAULT_INDEX = 99;

int main()
{
    cout << "Please enter a line of text:\n";
    string line_of_text;
    getline(cin, line_of_text);

    int frequency[NUM_OF_ALPHABETS + 1] = {0};

    char character;
    int index;
    for (int i = 0; i < line_of_text.length(); i++)
    {
        character = line_of_text[i];
        index = alphabetToIndex(character);
        if (index != DEFAULT_INDEX)
            frequency[index]++;
    }

    cout << frequency[NUM_OF_ALPHABETS] + 1 << "\twords\n";
    for (int i = 0; i < NUM_OF_ALPHABETS; i++)
    {
        if (frequency[i] != 0)
            cout << frequency[i] << '\t' << char('a' + i) << endl;
    }

    return 0;
}


int alphabetToIndex(char character)
{
    int index = DEFAULT_INDEX;
    if (character >= 'a' && character <= 'z')
        index = int(character - 'a');
    else if (character >= 'A' && character <= 'Z')
        index = int(character - 'A');
    else if (character == SPACE)
        index = NUM_OF_ALPHABETS;

    return index;
}