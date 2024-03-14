#include <bits/stdc++.h>

using namespace std;

string s;

void solve(void)
{
    cin >> s;

    int prv = -1;
    int nxt = -1;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '?')
            prv = i;
        else {
            while (i < s.size() && s[i] == '?')
                i++;
            nxt = i;
            if ((prv != -1 && s[prv] == '1') && (nxt == s.size() || s[nxt] == '1'))
                for (int i = prv + 1; i < nxt; i++)
                    s[i] = '1';
            else
                for (int i = prv + 1; i < nxt; i++)
                    s[i] = '0';

            prv = nxt;
        }
    }

    cout << s << '\n';
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while(t--)
        solve();
}