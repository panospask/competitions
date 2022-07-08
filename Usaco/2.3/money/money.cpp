/*
ID: panos.p1
LANG: C++
TASK: money
*/

#include <bits/stdc++.h>

using namespace std;

long long int v, n;
long long int coins[25];
long long int dp[10005];

int main(void)
{
    freopen("money.in", "r", stdin);
    freopen("money.out", "w", stdout);

    scanf("%lld %lld", &v, &n);
    for (int i = 0; i < v; i++)
        scanf("%lld", &coins[i]);

    dp[0] = 1;
    for (int i = 0; i < v; i++)
        for (int j = 0; j < n; j++)
            if (coins[i] + j <= n)
                dp[coins[i] + j] += dp[j];

    printf("%lld\n", dp[n]);
    return 0;
}