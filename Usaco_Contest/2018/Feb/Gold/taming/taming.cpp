#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;

// dp[i][j][k]: The minimum number of log changes for up to log[i] that occured if j breakouts happened, and the last one happened at day k
int dp[MAXN + 2][MAXN + 2][MAXN + 2];
int n;
int logged[MAXN + 2];

int main(void)
{
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &logged[i]);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            for (int k = 0; k <= n; k++)
                dp[i][j][k] = INT_MAX;

    dp[0][1][0] = (logged[0] != 0);
    for (int i = 0; i < n - 1; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 0; k < n; k++) {
                if (dp[i][j][k] == INT_MAX)
                    continue;

                // Add the next day assuming no breakout happened
                bool isconsist = (logged[i+1] == i+1-k);
                dp[i+1][j][k] = min(dp[i+1][j][k], dp[i][j][k] + !isconsist);

                // Add the next day assuming a breakout happened
                isconsist = (logged[i+1] == 0);
                dp[i+1][j+1][i+1] = min(dp[i+1][j+1][i+1], dp[i][j][k] + !isconsist);
            }

    int ans;
    for (int j = 1; j <= n; j++) {
        ans = INT_MAX;
        for (int k = 0; k < n; k++)
            ans = min(ans, dp[n-1][j][k]);

        printf("%d\n", ans);
    }

    return 0;
}