#include <bits/stdc++.h>

using namespace std;

string a, b;
vector<vector<int>> dp;

void solve(void)
{
    cin >> a >> b;

    dp.assign(a.size() + 1, vector<int>(b.size() + 1, 0));

    for (int i = 1; i <= a.size(); i++) {
        for (int j = 1; j <= b.size(); j++) {
            dp[i][j] = dp[i - 1][j];
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }


    int ans = 0;
    for (int j = 0; j <= b.size(); j++) {
        ans = max(ans, dp[a.size()][j]);
    }

    printf("%ld\n", a.size() + b.size() - ans);
}

int main(void)
{
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}