/*
ID: panos.p1
LANG: C++11
TASK: range
*/

#include <bits/stdc++.h>
#define MAXN 255

using namespace std;

typedef pair<int, int> ii;

// Is there a square with side length x starting at (i, j) ?
vector<vector<vector<bool>>> dp;
// Count of squares with side length x
int cnt[MAXN];
int n;

int main(void)
{
    freopen("range.in", "r", stdin);
    freopen("range.out", "w", stdout);

    scanf("%d", &n);
    int cur;
    dp.resize(n+5);
    for (int i = 0; i < n + 5; i++) {
        dp[i].resize(n+5);
        for (int j = 0; j < n + 5; j++)
            dp[i][j].resize(n+5);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            scanf("%1d", &cur);
            dp[1][i][j] = cur;
        }

    for (int x = 2; x <= n; x++) {
        cnt[x] = 0;
        for (int i = 0; i <= n - x; i++)
            for (int j = 0; j <= n - x; j++) {
                dp[x][i][j] = (dp[x-1][i][j] && dp[x-1][i+1][j] && dp[x-1][i][j+1] && dp[x-1][i+1][j+1]);
                if (dp[x][i][j])
                    cnt[x]++;
            }
    }

    for (int i = 2; i <= n; i++) {
        if (cnt[i] == 0)
            break;
        printf("%d %d\n", i, cnt[i]);
    }

    return 0;
}