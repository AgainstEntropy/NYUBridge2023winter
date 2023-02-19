# include <iostream>
# include <cmath>
using namespace std;

void analyzeDividors(int num, int& outCountDivs, int& outSumDivs);
bool isPerfect(int num);

const char SPACE = ' ';

int main()
{
    int m;
    cout << "Please enter an interger(>=2) to see if any perfect number is in the range of [2, M]: ";
    cin >> m;

    string perfect_nums = "Perfect numbers within [2, " + to_string(m) + "]: ";
    string amicable_num_pairs = "Amicable number pairs within [2, " + to_string(m) + "]: ";

    bool is_perfect;
    for (int i = 2; i <= m; i++)
    {
        if (isPerfect(i))
            perfect_nums += (to_string(i) + SPACE);
        else
        {
            int count_divs_1, sum_divs_1,
                count_divs_2, sum_divs_2;
            analyzeDividors(i, count_divs_1, sum_divs_1);
            if ((sum_divs_1 <= m) && (sum_divs_1 > i))
            {
                analyzeDividors(sum_divs_1, count_divs_2, sum_divs_2);
                if (sum_divs_2 == i)
                    amicable_num_pairs += "(" + to_string(i) + "," + to_string(sum_divs_1) + ") ";
            }
        }
    }
    
    cout << perfect_nums << endl;
    cout << amicable_num_pairs << endl;

    return 0;
}

void analyzeDividors(int num, int& outCountDivs, int& outSumDivs)
{
    outCountDivs = 0;
    outSumDivs = 0;
    if (num >= 2)
    {
        int div = sqrt(num);
        if (pow(div, 2) == num)
        {
            outCountDivs++;
            outSumDivs += div;
            div--;
        }

        while (div > 1)
        {
            if (num % div == 0)
            {
                outCountDivs += 2;
                outSumDivs += (div + num / div);
            }
            div--;
        }

        // Additional consideration of 1
        outCountDivs++;
        outSumDivs += 1;
    }
}

bool isPerfect(int num)
{
    int out_count_divs, out_sum_divs;
    analyzeDividors(num, out_count_divs, out_sum_divs);

    return (num == out_sum_divs) ? true : false;
}