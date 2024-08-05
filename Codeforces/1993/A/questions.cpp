#include <bits/stdc++.h>

using namespace std;

int N;
string s;

int code(char c)
{
    if (c == 'A') {
        return 0;
    }
    if (c == 'B') {
        return 1;
    }
    if (c == 'C') {
        return 2;
    }
    if (c == 'D') {
        return 3;
    }
    return 4;
}

void solve(void)
{
    cin >> N >> s;

    int cnt[5];
    cnt[0] = cnt[1] = cnt[2] = cnt[3] = cnt[4] = 0;
    int ans = 0;
    for (int i = 0; i < 4 * N; i++) {
        int v = code(s[i]);

        cnt[v]++;
        if (cnt[v] <= N && v != 4) {
            ans++;
        }
    }

    cout << ans << endl;
}

int main(void)
{
    ios::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}