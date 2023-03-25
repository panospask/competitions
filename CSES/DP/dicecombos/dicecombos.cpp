#include <bits/stdc++.h>
#define MAXN 1000000
#define MOD ((int)1e9 + 7)

using namespace std;

// Number of ways to construct i by throwing a dice
long long int dp[MAXN + 2];

int n;

int main(void)
{
    scanf("%d", &n);

    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int roll = 1; roll <= 6 && i - roll >= 0; roll++) {
            dp[i] += dp[i - roll];
            dp[i] %= MOD;
        }
    }   

    printf("%lld\n", dp[n]);
    return 0;
}