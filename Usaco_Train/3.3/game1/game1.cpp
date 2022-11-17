/*
ID: panos.p1
LANG: C++11
TASK: game1
*/

#include <bits/stdc++.h>
#define MAXN 100

using namespace std;
int dp[MAXN + 2][MAXN + 2];
int line[MAXN + 2];
int prefsums[MAXN + 2];
int n;

// Find the best combo from l to r, inclusive
int bestof(int l, int r)
{
    if (l == r)
        return line[l];

    if (dp[l][r] != -1)
        return dp[l][r]; 

    dp[l][r] = prefsums[r] - prefsums[l-1] - min(bestof(l+1, r), bestof(l, r-1));
    return dp[l][r];
}

int main(void)
{
    freopen("game1.in", "r", stdin);
    freopen("game1.out", "w", stdout);

    scanf("%d", &n);
    line[0] = 0;
    prefsums[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &line[i]);
        prefsums[i] = line[i] + prefsums[i-1];
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = -1;

    int ans = bestof(1, n);
    printf("%d %d\n", ans, prefsums[n] - ans);
    return 0;
}