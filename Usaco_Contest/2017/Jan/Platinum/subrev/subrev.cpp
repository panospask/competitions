#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 50
#define MAXV 50

using namespace std;

// dp[i][j][k][l]: Maximum value we can extract from the subsequence [i...j] given that
// the maximum element of the prefix is k, and the minimum of the suffix is l
int dp[MAXN + 2][MAXN + 2][MAXV + 2][MAXV + 2];
int n;
int a[MAXN + 2];

int calc_dp(int i, int j, int k, int l)
{
    if (k > l)
        return -1e6;
    if (i > j)
        return 0;
    if (dp[i][j][k][l] != -1)
        return dp[i][j][k][l];

    if (i == j) {
        dp[i][j][k][l] = (a[i] >= k && a[i] <= l);
        return dp[i][j][k][l];
    }

    int res = 0;
    // Swap a[i], a[j]
        if (a[j] >= k && a[j] <= l)
            res = max(res, 1 + calc_dp(i + 1, j - 1, a[j], l));
        if (a[i] >= k && a[i] <= l)
            res = max(res, 1 + calc_dp(i + 1, j - 1, k, a[i]));
        if (a[j] >= k && a[i] <= l)
            res = max(res, 2 + calc_dp(i + 1, j - 1, a[j], a[i]));
    else if (a[i] >= k && a[j] <= l)
        res = max(res, 2 + calc_dp(i + 1, j - 1, a[i], a[j]));

    // Only include/ exclude a[i]
    res = max(res, calc_dp(i + 1, j, k, l));
    if (a[i] >= k && a[i] <= l)
        res = max(res, 1 + calc_dp(i + 1, j, a[i], l));

    // Only include/exclude a[j]
    res = max(res, calc_dp(i, j - 1, k, l));
    if (a[j] >= k && a[j] <= l)
        res = max(res, 1 + calc_dp(i, j - 1, k, a[j]));

    res = max(res, calc_dp(i + 1, j - 1, k, l));

    dp[i][j][k][l] = res;
    return dp[i][j][k][l];
}

int main(void)
{
    freopen("subrev.in", "r", stdin);
    freopen("subrev.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    memset(dp, -1, sizeof(dp));
    printf("%d\n", calc_dp(0, n-1, 0, MAXV + 1));
}