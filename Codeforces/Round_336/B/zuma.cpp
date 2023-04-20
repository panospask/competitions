#include <bits/stdc++.h>
#define MAXN 500

using namespace std;

int n;
// dp[l][r]: Minimum number of seconds needed to destroy subarray [l..r]
int dp[MAXN + 2][MAXN + 2];
int a[MAXN + 2];

int calc_dp(int l, int r)
{
    if (r < l)
        return 0;
    else if (r == l)
        return 1;
    if (dp[l][r] != -1)
        return dp[l][r];

    dp[l][r] = 1 + calc_dp(l + 1, r);
    for (int i = l + 2; i <= r; i++)
        if (a[l] == a[i]) {
            // Remove the ones between them and form a palindrome
            dp[l][r] = min(dp[l][r], calc_dp(l + 1, i - 1) + calc_dp(i + 1, r));
        }

    if (a[l] == a[l+1])
        dp[l][r] = min(dp[l][r], calc_dp(l+2, r) + 1);

    return dp[l][r];
}

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        dp[i][i] = 1; // It is a palindrome and therefore can be destroyed in 1 sec
    }

    memset(dp, -1, sizeof(dp));

    printf("%d\n", calc_dp(0, n-1));
    return 0;
}