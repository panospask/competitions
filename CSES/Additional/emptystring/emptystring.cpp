#include <bits/stdc++.h>
#define MAXN 500
#define MOD ((int)1e9 + 7)

using namespace std;

int n;
// dp[l][r]: The total number of ways to completely delete the string [l...r]
long long int dp[MAXN + 2][MAXN + 2];
string s;
long long choose[MAXN / 2 + 2][MAXN / 2 + 2];

int main(void)
{
    cin >> s;
    n = s.size();

    choose[0][0] = 1;
    for (int len = 1; len <= n/2; len++) {
        choose[len][0] = choose[len][len] = 1;
        for (int i = 1; i < len; i++)
            choose[len][i] = (choose[len-1][i] + choose[len-1][i-1]) % MOD;
    }
    for (int l = 0; l <= n; l++)
        for (int r = l - 1; r >= 0; r--)
            dp[l][r] = 1;

    for (int len = 1; len <= n; len++)
        for (int l = 0; l <= n - len; l++) {
            int r = len + l - 1;
            if (l == r) {
                dp[l][r] = 0;
                continue;
            }
            else if (l + 1 == r) {
                dp[l][r] = s[l] == s[r];
                continue;
            }

            for (int i = l + 1; i <= r; i++) {
                if (s[l] == s[i]) {
                    long long ways = ((dp[l+1][i-1] * dp[i+1][r]) % MOD * choose[(r - l + 1) / 2][(i - l + 1) / 2]) % MOD;
                    dp[l][r] += ways;
                    dp[l][r] %= MOD; 
                }
            }
        }

    printf("%lld\n", dp[0][n-1]);
    return 0;
}