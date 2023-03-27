#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 500
#define MOD ((int)1e9 + 7)

using namespace std;

int n;
char grid[MAXN + 2][MAXN + 2];

// The number of palindromic paths starting at row i and ending at row j, length 2a + 1
long long dp[MAXN + 2][MAXN + 2];
long long prv[MAXN + 2][MAXN + 2];

int main(void)
{
    freopen("palpath.in", "r", stdin);
    freopen("palpath.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf(" %c", &grid[i][j]);

    for (int i = 0; i < n; i++)
        prv[i][i] = 1;

    for (int a = 1; a < n; a++) {
        for (int r1 = 0; r1 < n; r1++) {
            int c1 = n - 1 - r1 - a;
            if (c1 < 0) continue;

            for (int r2 = 0; r2 < n; r2++) {
                int c2 = n - 1 - r2 + a;
                if (c2 >= n) continue;

                dp[r1][r2] = 0;
                if (grid[r1][c1] != grid[r2][c2]) {
                    continue;
                }

                dp[r1][r2] += prv[r1][r2];
                if (r1 != n - 1) 
                    dp[r1][r2] += prv[r1 + 1][r2];
                if (r2 != 0)
                    dp[r1][r2] += prv[r1][r2 - 1];
                if (r1 != n - 1 && r2 != 0)
                    dp[r1][r2] += prv[r1 + 1][r2 - 1];

                dp[r1][r2] %= MOD;
            }
        }

        swap(dp, prv);
    }

    printf("%lld\n", prv[0][n-1]);
    return 0;
}