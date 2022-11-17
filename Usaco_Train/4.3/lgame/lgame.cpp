/*
ID: panos.p1
LANG: C++11
TASK: lgame
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define LETTERS 26
#define POS(i) (pow(10, i));

using namespace std;

int values[LETTERS] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};
int ttl_let = 0;
map<char, int> letnums;
map<int, char> revnums;
map<int, vector<string>> numreqs;
map<int, int> reqval;
int maxans = 0;
string origin;
vector<string> cur_combo;
string combo1;
string combo2;
vector<int> answ1;
vector<int> answ2;
int anscnt = 0;
set<string> answers;

ifstream dictstream;

int find_let_val(char c)
{
    return values[c - 'a'];
}

int let_to_num(char c, bool change)
{
    int num = letnums[c];

    if (num == 0) 
        if (change) {
            letnums[c] = ++ttl_let;
            revnums[ttl_let] = c;
        } 

    return num - 1;
}

int find_value(string& s)
{
    int curcnt = 0;
    int curdig;
    for (int i = 0; i < s.size(); i++) {
        curdig = let_to_num(s[i], false);
        curcnt += POS(curdig);
    }

    return curcnt;
}

void add_cur_digit_to_combo(int i)
{
    if (i >= origin.size()) {
        // Check for the added values of all the strings, etc...
        int curans = 0;
        
        int s1val = find_value(combo1);
        int s2val = find_value(combo2);

        curans += reqval[s1val];
        curans += reqval[s2val];

        if (curans > maxans) {
            maxans = curans;
            anscnt = 0;
            answ1.clear();
            answ2.clear();
        }
        if (curans == maxans) {
            answ1.pb(s1val);
            answ2.pb(s2val);
            anscnt++;
        }

        return;
    }

    // Add in string1
    combo1.pb(origin[i]);
    add_cur_digit_to_combo(i + 1);
    combo1.pop_back();

    // Add in string2
    combo2.pb(origin[i]);
    add_cur_digit_to_combo(i + 1);
    combo2.pop_back();

    // Don't add in any string
    add_cur_digit_to_combo(i + 1);

    return;
}

int main(void)
{
    freopen("lgame.in", "r", stdin);
    freopen("lgame.out", "w", stdout);
    dictstream.open("lgame.dict");

    cin >> origin;
    for (int i = 0; i < origin.size(); i++)
        let_to_num(origin[i], true);


    string cur;
    dictstream >> cur;
    int curnum;
    bool isgood = true;
    int curdig;
    int curval = 0;
    while (cur[0] != '.') {
        curnum = 0;
        curval = 0;
        isgood = true;
        for (int i = 0; i < cur.size() && isgood; i++) {
            curdig = let_to_num(cur[i], false);
            curval += find_let_val(cur[i]);
            if (curdig == -1) {
                isgood = false;
                break;
            }
            else {
                curnum += POS(curdig);
            }
        }   

        if (isgood) {
            numreqs[curnum].pb(cur);
            reqval[curnum] = curval;
        }

        dictstream >> cur;
    }

    add_cur_digit_to_combo(0);

    // Generate all possible answers
    vector<string> s1, s2;
    string ns;
    string val1, val2;
    for (int i = 0; i < anscnt; i++) {
        s1 = numreqs[answ1[i]];
        s2 = numreqs[answ2[i]];

        if (s1.empty()) {
            for (int d = 0; d < s2.size(); d++)
                answers.insert(s2[d]);
        }   
        else if (s2.empty()) {
            for (int d = 0; d < s1.size(); d++)
                answers.insert(s1[d]);
        }
        else {
            for (int d = 0; d < s1.size(); d++)
                for (int j = 0; j < s2.size(); j++) {
                    val1 = s1[d];
                    val2 = s2[j];
                    if (val1 > val2)
                        swap(val1, val2);

                    ns = val1 + ' ' + val2;
                    answers.insert(ns);
                }
        }
    }

    printf("%d\n", maxans);
    // sort(answers.begin(), answers.end());
    for (auto& l : answers)
        cout << l << '\n';

    return 0;
}