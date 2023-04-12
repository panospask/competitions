#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000
#define MAXK 10
#define MOD 1000000009

using namespace std;

// dp[i][j][k][l]: The total possible ways to make k winning pairs:
// With the subarrays [0...i] and [0...j]
long long int dp[MAXN + 2][MAXN + 2][MAXK + 2];
int a[MAXN + 2];
int b[MAXN + 2];
int n, m, r;

int main(void)
{
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);

    scanf("%d %d %d" ,&n, &m, &r);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &b[i]);

    sort(a + 1, a + n + 1);
    reverse(a + 1, a + n + 1);

    sort(b + 1, b + m + 1);
    reverse(b + 1, b + m + 1);

    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dp[i][j][0] = 1; // Exactly 1 way to make 0 pairs, don't take any cow

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) 
            for (int k = 1; k <= r; k++) {
                // Possibilities of not building the pair (i, j)
                dp[i][j][k] = (dp[i-1][j][k] + dp[i][j-1][k] - dp[i-1][j-1][k]) % MOD;

                // Build the pair (i, j) if it is favourable to fj
                if (a[i] > b[j]) {
                    dp[i][j][k] += dp[i-1][j-1][k-1];
                }

                dp[i][j][k] = (dp[i][j][k] + MOD) % MOD;
            }

    printf("%lld\n", dp[n][m][r]);
    return 0;
                
}