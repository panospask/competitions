#include <bits/stdc++.h>

using namespace std;

string s;

void solve(void) {
    cin >> s;
    int N = s.size();

    int cnt = 0;
    int ans = 0;
    if (s[0] != 's') {
        ans++;
        s[0] = 's';
    }
    if (s.back() != 's') {
        ans++;
        s.back() = 's';
    }

    for (int i = 1; i < s.size(); i++) {
        if (s[i] == 'u') {
            cnt++;
        }
        else {
            ans += cnt / 2;
            cnt = 0;
        }
    }

    cout << ans << endl;
}

int main(void) {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}