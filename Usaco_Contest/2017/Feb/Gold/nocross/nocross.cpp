#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000

using namespace std;

// dp[i][j]: Max roads one can build up to i-th farm on the bottom and j-th farm on the top
long long int dp[MAXN + 2][MAXN + 2];
int n;

int bottom[MAXN + 2];
int top[MAXN + 2];

int main(void)
{
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &bottom[i]);
    for (int j = 1; j <= n; j++)
        scanf("%d", &top[j]);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            dp[i][j] = 0;
            dp[i][j] = max(dp[i][j], dp[i-1][j]);
            dp[i][j] = max(dp[i][j], dp[i][j-1]);
            dp[i][j] = max(dp[i][j], dp[i-1][j-1] + (abs(bottom[i] - top[j]) <= 4));
        }

    printf("%lld\n", dp[n][n]);
    return 0;
}