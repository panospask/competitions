#include <bits/stdc++.h>
#define MOD ((int)1e9 + 7)
#define MAXN 100
#define MAXPEN 5000

using namespace std;

// dp[i][j][k]: total sum of teams up to coder i, with j not finished teams and k penalty
long long int dp[MAXN + 1][MAXN + 1][MAXPEN * 2 + 1];
int n, x;
int s[MAXN + 1];

int main(void)
{
    scanf("%d %d", &n, &x);
    for (int i = 0; i < n; i++)
        scanf("%d", &s[i]);
    sort(s, s + n);

    for (int i = 0; i <= n; i++) {
        for (int k = 0; k <= 2 * MAXPEN; k++)
            dp[0][i][k] = 0;
    }
    dp[0][0][MAXPEN] = 1;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j <= n - i; j++)
            for (int k = 0; k <= x + MAXPEN; k++) {
                if (dp[i][j][k] == 0) continue;

                // Add i to one of the current teams
                dp[i + 1][j][k] += j * dp[i][j][k] % MOD;
                dp[i + 1][j][k] %= MOD;

                dp[i + 1][j][k] += dp[i][j][k];

                // Close one of the teams with i
                if (j > 0 && x + MAXPEN >= k + s[i])
                    dp[i + 1][j - 1][k + s[i]] += dp[i][j][k] * j;
                    dp[i + 1][j - 1][k + s[i]] %= MOD;

                // Open a new team with i
                if (j + 1 <= n - (i + 1))
                    dp[i + 1][j + 1][k - s[i]] += dp[i][j][k];
                    dp[i + 1][j + 1][k - s[i]] %= MOD;
            }

    long long int ans = 0;
    for (int k = MAXPEN; k <= x + MAXPEN; k++) {
        ans += dp[n][0][k];
        ans %= MOD;
    }

    printf("%lld\n", ans);
    return 0;
}