# include <iostream>
using namespace std;

int alphabetToIndex(char character);
void getFrequency(string text, int frequency[]);
bool isAnagrams(int freq1[], int freq2[]);

const int NUM_OF_ALPHABETS = 26;
const int DEFAULT_INDEX = 99;

int main()
{
    string string1("Eleven plus two"), string2("Twelve plus one");

    int freq1[NUM_OF_ALPHABETS] = {0},
        freq2[NUM_OF_ALPHABETS] = {0};

    getFrequency(string1, freq1);
    getFrequency(string2, freq2);

    cout << (isAnagrams(freq1, freq2) ? "Two strings are anagrams." : "Two strings are not anagrams.") << endl;

    return 0;
}

int alphabetToIndex(char character)
{
    int index = DEFAULT_INDEX;
    if (character >= 'a' && character <= 'z')
        index = int(character - 'a');
    else if (character >= 'A' && character <= 'Z')
        index = int(character - 'A');

    return index;
}

void getFrequency(string text, int frequency[])
{
    char character;
    int index;
    for (int i = 0; i < text.length(); i++)
    {
        character = text[i];
        index = alphabetToIndex(character);
        if (index != DEFAULT_INDEX)
            frequency[index]++;
    }
}

bool isAnagrams(int freq1[], int freq2[])
{
    bool is_anagrams = true;
    for (int i = 0; i < NUM_OF_ALPHABETS; i++)
    {
        if (freq1[i] != freq2[i])
        {
            is_anagrams = false;
            break;
        }
    }

    return is_anagrams;
}