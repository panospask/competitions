#include <bits/stdc++.h>

using namespace std;

int n, t;
string s;

void solve(void)
{
    cin >> n >> s;

    int ans = 0, smaller = 0, larger = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '<') {
            larger = 0;
            smaller++;
            ans = max(ans, smaller);
        }
        else {
            smaller = 0;
            larger++;
            ans = max(ans, larger);
        }
    }

    cout << ans + 1 << '\n';
}

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> t;
    while (t--)
        solve();
}