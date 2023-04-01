#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

typedef pair<int, int> ii;

int dp[MAXN + 2];
int a[MAXN + 2], b[MAXN  + 2];
int pos[MAXN + 2], c[MAXN  + 2];
int n;

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        pos[a[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
        c[i] = pos[b[i]];
    }

    for (int i = 1; i <= n + 1; i++)
        dp[i] = INT_MAX;
    dp[0] = INT_MIN;

    for (int i = 1; i <= n; i++) {
        int curval = c[i-1];

        int l = 0;
        int r = n + 1;
        while (r > l + 1) {
            int mid = (l + r) / 2;
            if (dp[mid] < curval)
                l = mid;
            else 
                r = mid;
        }

        dp[l+1] = curval;
    }

    int ans = 0;
    while (dp[ans + 1] != INT_MAX)
        ans++;
    printf("%d\n", ans);
    return 0;
}