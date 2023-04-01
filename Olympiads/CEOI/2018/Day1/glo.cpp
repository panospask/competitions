#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int n, x;
int a[MAXN + 2];

vector<int> dp;

int inc_lis[MAXN + 2];
int dec_lis[MAXN + 2];
bool cont[MAXN + 2];

int main(void)
{
    scanf("%d %d", &n, &x);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    dp.resize(n + 1);

    for (int i = 0; i < n + 1; i++) {
        dp[i] = INT_MAX;
    }
    dp[0] = INT_MIN;
    for (int i = 1; i <= n; i++) {
        int curval = a[i];

        int l = 0;
        int r = n;
        while (r > l + 1) {
            int mid = (l + r) / 2;
            if (dp[mid] < curval)
                l = mid;
            else 
                r = mid;
        }

        dp[l+1] = curval;
        inc_lis[i] = l+1;
    }

    int ans = 0;

    // Find decreasing subsequence of reverse array and simultaneously check answers
    for (int i = 0; i <= n; i++)
        dp[i] = INT_MIN;
    dp[0] = INT_MAX;

    for (int i = n; i > 0; i--) {
        // Check answers
        int curval = a[i];
        int rev_val = n - (upper_bound(dp.rbegin(), dp.rend(), curval - x) - dp.rbegin());

        ans = max(ans, rev_val + inc_lis[i]);

        int l = 0;
        int r = n;
        while (r > l + 1) {
            int mid = (l + r) / 2;
            if (dp[mid] > curval)
                l = mid;
            else 
                r = mid;
        }

        dp[r] = curval;
    }

    printf("%d\n", ans);
    return 0;
}