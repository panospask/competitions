#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 300
#define INF 1e9

using namespace std;

// dp[i][j]: The minimum number of brush strokes needed to cover the region [i..j]
int dp[MAXN + 2][MAXN + 2];
int n;

int a[MAXN + 2];

int main(void)
{
    // freopen("modernart.in", "r", stdin);
    // freopen("modernart.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int len = 1; len <= n; len++)
        for (int l = 0; l <= n - len; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;

            if (l == r) {
                // We can just do a 1-unit stroke
                dp[l][r] = 1;
                continue;
            }

            for (int i = l; i < r; i++) 
                dp[l][r] = min(dp[l][r], dp[l][i] + dp[i+1][r]);

            if (a[l] == a[r]) {
                // We can save a colour by painting the bottom layer with a[l]
                dp[l][r]--;
            }
        }

    printf("%d\n", dp[0][n-1]);
    return 0;
}