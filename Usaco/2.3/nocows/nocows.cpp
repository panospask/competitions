/*
ID: panos.p1
LANG: C++
TASK: nocows
*/

#include <bits/stdc++.h>
#define MODNUM 9901

using namespace std;

long long int dp[202][202];
int n, k;
long long int ans;

int main(void)
{
    freopen("nocows.in", "r", stdin);
    freopen("nocows.out", "w", stdout);

    scanf("%d %d", &n, &k);

    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; i++) {
        dp[0][i] = 0;
        dp[1][i] = 1;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 2; j <= k; j++) {
            for (int x = 1; x <= i - 1; x++) {
                dp[i][j] += dp[x][j - 1] * dp[i - x - 1][j - 1];
                dp[i][j] %= MODNUM;
            }
        }

    long long int ans = dp[n][k] - dp[n][k-1];
    ans %= MODNUM;
    ans += MODNUM;
    ans %= MODNUM;

    printf("%lld\n", ans);
    return 0;
}