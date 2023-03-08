# include <iostream>
using namespace std;

int alphabetToIndex(char character);

const char SPACE = ' ';

int main()
{
    cout << "Please enter a line of text:\n";
    string line_of_text;
    getline(cin, line_of_text);

    int frequency[27] = {0};

    char character;
    for (int i = 0; i < line_of_text.length(); i++)
    {
        character = line_of_text[i];
        frequency[alphabetToIndex(character)]++;
    }

    cout << frequency[26] + 1 << "\twords\n";
    for (int i = 0; i < 26; i++)
    {
        if (frequency[i] != 0)
            cout << frequency[i] << '\t' << char('a' + i) << endl;
    }

    return 0;
}


int alphabetToIndex(char character)
{
    int index;
    if (character >= 'a' && character <= 'z')
        index = int(character - 'a');
    else if (character >= 'A' && character <= 'Z')
        index = int(character - 'A');
    else if (character == SPACE)
        index = 26;

    return index;
}