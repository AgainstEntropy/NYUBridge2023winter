# include <iostream>
using namespace std;

bool isPureNum(string text, int &startIndex, int &endIndex);
void replaceWithX(string &text, int startIndex, int endIndex);

const char SPACE = ' ';

int main()
{
    cout << "Please enter a line of text:\n";
    string text;
    getline(cin, text);

    int i = 0, j = 0;
    const int len = text.length();
    while (j < len)
    {
        if (isPureNum(text, i, j)) replaceWithX(text, i, j);
        j++;
        i = j;
    }

    cout << text;
    return 0;
}

bool isPureNum(string text, int &startIndex, int &endIndex)
{
    bool is_pure_num = true;
    char c;
    while (endIndex < text.length())
    {
        c = text[endIndex];
        if (c == SPACE) break;
        else if (is_pure_num && !isdigit(c)) is_pure_num = false;
        endIndex++;
    }

    return is_pure_num;
}

void replaceWithX(string &text, int startIndex, int endIndex)
{
    for (int k = startIndex; k < endIndex; k++)
        text[k] = 'x';
}
