#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 400

using namespace std;

int grass[MAXN + 10][MAXN + 10];
int ttl_reachable[MAXN + 10][MAXN + 10];
int n, k;

int main(void)
{
    freopen("lazy.in", "r", stdin);
    freopen("lazy.out", "w", stdout);

    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= n; j++) 
            scanf("%d", &grass[i][j]);

    // Calculate ttl_reachable from (0, 0)
    for (int i = 0; i <= min(n, k); i++)
        for (int j = 0; j + i <= k && j <= n; j++)
            ttl_reachable[0][0] += grass[i][j];

    // Calculate ttl_reachable from (x, 0)
    for (int y = 1; y <= n; y++) {
        ttl_reachable[y][0] = ttl_reachable[y - 1][0];
        for (int l = 0; l <= k; l++) {
            // Remove reachable only from (y - 1, 0)
            if (y - 1 - l >= 0 && k - l <= n)             
                ttl_reachable[y][0] -= grass[y - 1 - l][k - l];   

            // Add reachable only from (y, 0)
            if (y + l <= n && k - l <= n)
                ttl_reachable[y][0] += grass[y + l][k - l];
        }
    }

    // Calculate everything else via that row by row
    int ans = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++) {
            if (j == 0)
                continue;

            ttl_reachable[i][j] = ttl_reachable[i][j - 1];
            for (int l = 0; l <= k; l++) {
                // Remove reachable only from (i, j-1)
                if (i - l >= 0 && j - 1 - k + l >= 0 && j - 1 - k + l <= n)
                    ttl_reachable[i][j] -= grass[i - l][j - 1 - k + l];
                if (i + l >= 0 && i + l != i - l && i + l <= n && j - 1 - k + l <= n && j - 1 - k + l >= 0)
                    ttl_reachable[i][j] -= grass[i + l][j - 1 - k + l];

                // Add reachable only from (i, j)
                if (i - l >= 0 && j + k - l >= 0 && j + k - l <= n)
                    ttl_reachable[i][j] += grass[i - l][j + k - l];
                if (i + l <= n  && i + l != i - l && j + k - l >= 0 && j + k - l <= n)
                    ttl_reachable[i][j] += grass[i + l][j + k - l];
            }


            if (ttl_reachable[i][j] > ans)
                ans  = ttl_reachable[i][j];
        }

    printf("%d\n", ans);
    return 0;
}