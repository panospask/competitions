#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

typedef pair<int, int> ii;

int cnt[MAXN + 2];
int dp[MAXN + 2];
ii x[MAXN + 2];
int n;

int main(void)
{
    // freopen("pcb.in", "r", stdin);
    // freopen("pcb.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &x[i].first, &x[i].second);

    sort(x + 1, x + 1 + n);
    dp[0] = INT_MAX;
    for (int i = 1; i <= n + 1; i++)
        dp[i] = INT_MIN;

    for (int i = 1; i <= n; i++) {
        int curval = x[i].second;

        int l = 0;
        int r = n + 1;
        while (r > l + 1) {
            int mid = (l + r) / 2;
            if (dp[mid] >= curval)
                l = mid;
            else 
                r = mid;
        }

        dp[l+1] = curval;
        cnt[l+1]++;
    } 

    int ans = 0;
    while (dp[ans+1] != INT_MIN)
        ans++;
    printf("%d\n", ans);
    return 0;
}