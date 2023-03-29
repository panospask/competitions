#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

// dp[i]: Minimum end value of subsequence of length i
int dp[MAXN  +2];
int n;
int a[MAXN + 2];

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = 1; i <= n; i++)
        dp[i] = INT_MAX;
    dp[0] = INT_MIN;
    dp[n+1] = INT_MAX;

    for (int i = 0; i < n; i++) {
        int curval = a[i];
        // Find the maximum subsequence of length cuval using binary search (i such that dp[i] < curval and dp[i+1] > curval)

        int l = 0;
        int r = n + 1;
        while (r > l + 1) {
            int mid = (l + r) / 2;
            if (dp[mid] < curval)
                l = mid;
            else 
                r = mid;
        }

        int ind = l;
        if (dp[l] < curval && dp[l+1] > curval) {
            // Use the subsequence up to l and add the latest value for a subseq of i + 1 with min val curval
            dp[l+1] = curval;
        }
    }

    int ans = 0;
    while (dp[ans + 1] != INT_MAX)
        ans++;

    printf("%d\n", ans);
    return 0;
}