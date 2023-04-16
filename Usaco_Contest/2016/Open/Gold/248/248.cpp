#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 248

using namespace std;

// dp[l][r]: The maximum value we can have in the range l, r if we use all of the numbers in there
int dp[MAXN + 2][MAXN + 2];
int a[MAXN + 2];
int n;
int ans = 0;

int main(void)
{
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    memset(dp, -1, sizeof(dp));
    for (int len = 1; len <= n; len++) 
        for (int l = 0; l <= n - len; l++) {
            int r = l + len - 1;

            if (l == r) {
                dp[l][r] = a[l];
                ans = max(ans, dp[l][r]);
                continue;
            }

            // Check all kinds of prefix-suffixes
            for (int i = l; i < r; i++) {
                if (dp[l][i] == -1 || dp[i+1][r] == -1)
                    continue;

                if (dp[l][i] == dp[i+1][r])
                    dp[l][r] = dp[l][i] + 1;
            }

            ans = max(ans, dp[l][r]);
        }

    printf("%d\n", ans);
    return 0;
}