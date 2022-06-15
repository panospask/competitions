/*
ID: panos.p1
LANG: C++
TASK: namenum
*/

#include <bits/stdc++.h>

#define pb push_back

using namespace std;

string words[5005];
int wordend = 0;
int cur_word_cnt = 0;
bool none = true;

char letters[10][3] = {{}, {}, {'A', 'B', 'C'}, {'D', 'E', 'F'}, {'G', 'H', 'I'}, {'J', 'K', 'L'}, {'M', 'N', 'O'}, {'P', 'R', 'S'}, {'T', 'U', 'V'}, {'X', 'Y', 'Z'}}; 

void check_for_words(string& to_check)
{
    while (cur_word_cnt != wordend) {
        if (words[cur_word_cnt] == to_check) {
            cout << words[cur_word_cnt] << '\n';
            cur_word_cnt++;
            none = false;
            break;
        }
        else if (words[cur_word_cnt] > to_check) {
            break;
        }
        else 
            cur_word_cnt++;
    }

    return;
}

void dfs(int pos, vector<int>& serial, string& to_check)
{
    if (pos == serial.size()) {
        check_for_words(to_check);
        return;
    }

    for (int i = 0; i < 3; i++) {
        to_check[pos] = letters[serial[pos]][i];
        dfs(pos + 1, serial, to_check);
    }

    return;
}

int main(void)
{
    freopen("namenum.in", "r", stdin);
    freopen("namenum.out", "w", stdout);

    long long int num;
    cin >> num;

    ifstream Ifile("dict.txt");
    int i = 0;
    while (true) {
        if (Ifile.eof())
            break;

        Ifile >> words[wordend++];
    }
    wordend--;

    vector<int> ser_num;

    for (long long int i = num; i > 0; i /= 10) {
        ser_num.pb(i % 10);
    }
    reverse(ser_num.begin(), ser_num.end());

    string to_check;
    to_check.resize(ser_num.size());

    dfs(0, ser_num, to_check);

    if (none)
        printf("NONE\n");

    return 0;
}