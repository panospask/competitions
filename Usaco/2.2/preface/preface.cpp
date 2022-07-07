/*
ID: panos.p1
LANG: C++
TASK: preface
*/

#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair

typedef pair<int, char> ii;

string letter[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
int val[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
vector<ii> cnt;

void subtract_num(int& number, int i)
{
    int times = number / val[i];

    for (char c : letter[i]) {
        for (auto& v : cnt)
            if (v.second == c) {
                v.first += times;
                break;
            }
    }

    number -= times * val[i];
}

void calc_number(int number)
{
    int i = 0;
    while (number > 0) {
        if (val[i] <= number)
            subtract_num(number , i);

        i++;
    }
}

int main(void)
{
    freopen("preface.in", "r", stdin);
    freopen("preface.out", "w", stdout);

    cnt.pb(mp(0, 'I'));
    cnt.pb(mp(0, 'V'));
    cnt.pb(mp(0, 'X'));
    cnt.pb(mp(0, 'L'));
    cnt.pb(mp(0, 'C'));
    cnt.pb(mp(0, 'D'));
    cnt.pb(mp(0, 'M'));

    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        calc_number(i);

    for (auto val : cnt) {
        if (val.first == 0)
            break;
        printf("%c %d\n", val.second, val.first);
    }

    return 0;
}