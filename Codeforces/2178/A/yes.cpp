#include <bits/stdc++.h>

using namespace std;

string s;

void solve(void) {
    cin >> s;

    int cnt = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'Y') {
            cnt++;
        }
    }

    if (cnt >= 2) {
        cout << "NO" << endl;
    }
    else {
        cout << "YES" << endl;
    }
}

int main(void) {
    ios::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}