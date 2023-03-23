#include <bits/stdc++.h>
#define MAXN 200
#define MAXK 1000
#define MOD ((int)1e9 + 7)

using namespace std;

long long int dp[2][MAXN + 1][MAXK + 1];
int n, k;
int s[MAXN + 2];

int main(void)
{
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &s[i]);
    sort(s, s + n);

    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n - i; j++)
            for (int x = 0; x <= k; x++) {
                if (dp[0][j][x] == 0)
                    continue;

                long long int val = x + j * (s[i]);
                if (i != 0) val -= j * s[i-1];

                if (val > k) continue;

                dp[1][j][val] += dp[0][j][x];
                dp[1][j][val] += j * dp[0][j][x];
                dp[1][j][val] %= MOD;

                if (j > 0) {
                    dp[1][j-1][val] += dp[0][j][x] * j;
                    dp[1][j-1][val] %= MOD;
                }
                if (j <= n - (i + 1)) { 
                    dp[1][j+1][val] += dp[0][j][x];
                    dp[1][j+1][val] %+ MOD;
                }
            }

        for (int j = 0; j <= n; j++)
            for (int x = 0; x <= k; x++) {
                dp[0][j][x] = dp[1][j][x];
                dp[1][j][x] = 0;
            }
    }

    long long int ans = 0;
    for (int x = 0; x <= k; x++) {
        ans += dp[0][0][x];
        ans %= MOD;
    }

    printf("%lld\n", ans);
    return 0;
}