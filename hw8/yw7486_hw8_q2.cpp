# include <iostream>
using namespace std;

bool isPalindrome(string str);

int main()
{
    cout << "Please enter a word: ";
    string str;
    cin >> str;

    if (isPalindrome(str))
        cout << str << " is a palindrome";
    else
        cout << str << " is not a palindrome";

    return 0;
}

bool isPalindrome(string str)
{
    int len = str.length();
    for (int i = 0; i < len/2 + 1; i++)
        if (str[i] != str[len-1-i]) return false;
    return true;
}