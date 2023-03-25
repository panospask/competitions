#include <bits/stdc++.h>
#define MAXX 1000000
#define MAXN 100

using namespace std;

// dp[i] : Minimum number of coins needed to get to the sum i
int dp[MAXX + 2];

int coins[MAXN + 2];
int x, n;

int main(void)
{
    scanf("%d %d", &n, &x);
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);
    sort(coins, coins + n);

    dp[0] = 0; // Can get to 0 without using any coins
    for (int s = 1; s <= x; s++) {
        dp[s] = 1e9;
        for (int i = 0; i < n && coins[i] <= s; i++)
            dp[s] = min(dp[s], dp[s - coins[i]] + 1);
    }

    if (dp[x] == 1e9)
        dp[x] = -1;
    printf("%d\n", dp[x]);
    return 0;
}