#include <bits/stdc++.h>

using namespace std;

string s;

void generate_full(int i)
{
    for (int j = 0; j < i; j++)
        cout << '(';
    for (int j = 0; j < i; j++)
        cout << ')';
}

void solve(void)
{
    cin >> s;

    bool seencl = false;
    bool aftercl = false;
    for (int i = 0; i < s.size(); i++) {
        seencl = seencl || s[i] == ')';
        aftercl = aftercl || (seencl && s[i] == '(');
    }

    if (s.size() == 2 && s == "()") {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
    if (aftercl)
        generate_full(s.size());
    else {
        for (int i = 0; i < s.size(); i++)
            cout << "()";
    }

    cout << endl;
}

int main(void)
{
    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}