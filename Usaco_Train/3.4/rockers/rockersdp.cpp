/*
ID: panos.p1
LANG: C++11
TASK: rockers
*/

#include <bits/stdc++.h>
#define MAXN 25

using namespace std;
int n, m, t;
int dp[MAXN][MAXN][MAXN];
int discs[MAXN];
int ans = 0;

int main(void)
{
    freopen("rockers.in", "r", stdin);
    freopen("rockers.out", "w", stdout);
    scanf("%d %d %d", &n, &t, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &discs[i]);

    for (int a = 0; a < m; a++) //Cur CD
        for (int b = 0; b <= t; b++) //Time remaining in cur CD
            for (int c = 0; c <= n; c++) {//Last song we used
                for (int d = c + 1; d <= n; d++) {//Song we want to use
                    if (discs[d] + b <= t)
                        dp[a][b + discs[d]][d] = max(dp[a][b + discs[d]][d], dp[a][b][c] + 1);
                    else if (discs[d] <= t)
                        dp[a + 1][discs[d]][d] = max(dp[a+1][discs[d]][d], dp[a][b][c] + 1);
                }
                ans = max(ans, dp[a][b][c]);
            }

    printf("%d\n", ans);
    return 0;
}