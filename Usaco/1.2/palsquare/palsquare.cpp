/*
ID: panos.p1
LANG: C++
TASK: palsquare
*/

#include <bits/stdc++.h>

#define pb push_back

using namespace std;

char numbers[20] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

string transform_to(int base, int number)
{
    string num;
    while (number > 0) {
        int curdig = number % base;
        num.pb(numbers[curdig]);
        number /= base;
    }

    reverse(num.begin(), num.end());

    return num;
}

bool check_pal(string s)
{
    bool pal = true;
    for (int i = 0; i < s.length() / 2 && pal; i++)
        if (s[i] != s[s.length() - i - 1])
            pal = false;

    return pal;
}

int main(void)
{
    freopen("palsquare.in", "r", stdin);
    freopen("palsquare.out", "w", stdout);

    int b;
    scanf("%d", &b);

    for (int i = 1; i <= 300; i++) {
        int sqr = i * i;
        string s = transform_to(b, sqr);
        if (check_pal(s)) {
            cout << transform_to(b, i) << ' ' << s << '\n';
        }
    }

    return 0;
}