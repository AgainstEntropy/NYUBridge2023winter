# include <iostream>
using namespace std;

string* createWordsArray(string sentence, int& outWordsArrSize);
int countWords(string sentence);

const char SPACE = ' ';

int main() {
    string sentence("You can do it");
    
    int out_words_arr_size;
    string* words_array = createWordsArray(sentence, out_words_arr_size);

    for (int i = 0; i < out_words_arr_size; i++) {
        cout << words_array[i] << endl;
    }
    delete [] words_array;
    words_array = nullptr;
    
    return 0;
}

string* createWordsArray(string sentence, int& outWordsArrSize) {
    outWordsArrSize = countWords(sentence);
    int word_len;
    string word(""), *words_array = new string[outWordsArrSize];
    for (int i = 0; i < outWordsArrSize; i++) {
        word_len = sentence.find(SPACE);
        words_array[i] = sentence.substr(0, word_len);
        sentence = sentence.substr(word_len + 1, sentence.length());
    }

    return words_array;
}

int countWords(string sentence) {
    int word_len, num_of_words = 0;
    string word("");
    while (word != sentence) {
        word_len = sentence.find(SPACE);
        word = sentence.substr(0, word_len);
        sentence = sentence.substr(word_len + 1, sentence.length());
        num_of_words++;
    }

    return num_of_words;
}