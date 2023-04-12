#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000
#define MAXM 26

using namespace std;

int adj[MAXM + 2][MAXM + 2];
int d[MAXM + 2][MAXM + 2];

// dp[i][j]: The way to reach i with the last streak being completed and being the letter j
long long int dp[MAXN + 2][MAXM + 2];
int s[MAXN + 2];

// changecost[i][j]: How much it costs to change the subarray[1..i] to [j]
long long int changecost[MAXN + 2][MAXM + 2];
int n, m, k;

void calc_distances(void)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            d[i][j] = adj[i][j];

    for (int k = 0; k < m; k++)
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    return;
}

int main(void)
{
    freopen("cowmbat.in", "r", stdin);
    freopen("cowmbat.out", "w", stdout);

    scanf("%d %d %d", &n, &m, &k);
    getchar();
    for (int i = 1; i <= n; i++)
        s[i] = getchar() - 'a';

    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &adj[i][j]);

    calc_distances();

    for (int c = 0; c < m; c++) {
        changecost[0][c] = 0;
        for (int i = 1; i <= n; i++) {
            changecost[i][c] = changecost[i-1][c] + d[s[i]][c];
        }
    }

    for (int i = 0; i <= n; i++)
        for (int c = 0; c < m; c++)
            dp[i][c] = LONG_LONG_MAX;

    for (int c = 0; c < m; c++)
        dp[k][c] = changecost[k][c]; // You can reach to k with active char ONLY by changing the first k characters

    for (int i = k; i < n; i++) {
        for (int c = 0; c < m; c++) {
            if (dp[i][c] == LONG_LONG_MAX)
                continue;

            // Continue the current streak
            dp[i+1][c] = min(dp[i+1][c], dp[i][c] + changecost[i+1][c] - changecost[i][c]);

            // Or build a new one (minimum size k)
            if (i + k <= n) {
                for (int c2 = 0; c2 < m; c2++)
                    dp[i+k][c2] = min(dp[i+k][c2], dp[i][c] + changecost[i+k][c2] - changecost[i][c2]);
            }
        }
    }

    long long int ans = LONG_LONG_MAX;
    for (int c = 0; c < m; c++)
        ans = min(ans, dp[n][c]);

    printf("%lld\n", ans);
    return 0;
}