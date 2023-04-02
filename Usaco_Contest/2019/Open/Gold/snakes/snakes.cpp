#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 400

using namespace std;

// dp[i][j][k]: Minimum total cost of catching the first i snakes with j changes, the last one occuring at k
long long int dp[2][MAXN + 1][MAXN + 1];

int maxsnake[2][MAXN +1][MAXN + 1];
long long int latest_sum[2][MAXN + 1][MAXN + 1];
int n, c;

int a[MAXN + 2];

int main(void)
{
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);

    scanf("%d %d", &n, &c);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int j = 0; j <= c; j++)
        for (int k = 0; k <= n; k++)
            dp[0][j][k] = dp[1][j][k] = LONG_LONG_MAX;

    // for (int k = 0; k < n; k++)
        // dp[0][0][k] = 0;
    dp[0][0][0] = 0;
    maxsnake[0][0][0] = a[0];
    latest_sum[0][0][0] = a[0];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j <= c; j++)
            for (int k = 0; k <= i; k++) {
                if (dp[0][j][k] == LONG_LONG_MAX)
                    continue;

                int newsnake = a[i+1];
                
                // Add the next snake to the current net
                int msnake = max(maxsnake[0][j][k], newsnake);
                long long int s = latest_sum[0][j][k] + newsnake;
                if (dp[0][j][k] + (i-k+2) * msnake - s - (i-k+1) * maxsnake[0][j][k] + latest_sum[0][j][k] < dp[1][j][k]) {
                    dp[1][j][k] = dp[0][j][k] + (i-k+2) * msnake - s - (i-k+1) * maxsnake[0][j][k] + latest_sum[0][j][k];
                    maxsnake[1][j][k] = msnake;
                    latest_sum[1][j][k] = s;
                }

                // Create a new net
                if (j != c && dp[1][j+1][i+1] > dp[0][j][k]) {
                    dp[1][j+1][i+1] = dp[0][j][k];
                    latest_sum[1][j+1][i+1] = newsnake;
                    maxsnake[1][j+1][i+1] = newsnake;
                }
            }

        for (int j = 0; j <= c; j++)    
            for (int k = 0; k <= n; k++) {
                dp[0][j][k] = dp[1][j][k];
                dp[1][j][k] = LONG_LONG_MAX;

                maxsnake[0][j][k] = maxsnake[1][j][k];
                latest_sum[0][j][k] = latest_sum[1][j][k];
            }
    }



    long long int ans = LONG_LONG_MAX;
    for (int k = 0; k < n; k++)
        ans = min(ans, dp[0][c][k]);
    
    printf("%lld\n", ans);
    return 0;
}