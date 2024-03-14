#include <bits/stdc++.h>

using namespace std;

int n;

const int INF = 1e6;

vector<int> a;
vector<int> best_by_col;
vector<vector<int>> dp;

void solve(void)
{
    scanf("%d", &n);

    dp.assign(n, vector<int>(2, 0));
    best_by_col.assign(n, -INF);
    a.resize(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i]--;
    }

    dp[0][false] = dp[0][true] = 0;
    best_by_col[a[0]] = 1;
    for (int i = 1; i < n; i++) {
        dp[i][false] = max(dp[i][false], dp[i - 1][true]);

        dp[i][true] = max(dp[i][true], dp[i][false]);

        if (best_by_col[a[i]] != -INF);
            dp[i][true] = max(dp[i][true], best_by_col[a[i]] + i);

        best_by_col[a[i]] = max(best_by_col[a[i]], dp[i][false] - i + 1);
    }

    printf("%d\n", dp[n - 1][true]);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}