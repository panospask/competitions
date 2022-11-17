/*
ID: panos.p1
LANG: C++11
TASK: theme
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 5000

using namespace std;

// Let dp[i][j] be the length of the matching, non-overlapping sequence ending at i, j
int dp[2][MAXN + 5];

int diffarr[MAXN + 5];
int n;

int main(void)
{
    freopen("theme.in", "r", stdin);
    freopen("theme.out", "w", stdout);

    scanf("%d", &n);
    int prevnum;
    scanf("%d", &prevnum);
    int curnum;
    for (int i = 1; i < n; i++) {
        scanf("%d", &curnum);
        diffarr[i] = curnum - prevnum;
        prevnum = curnum;
    }
    diffarr[0] = 10e3; // Impossible

    for (int i = 0; i <= n; i++) {
        dp[0][i] = 0;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        // As is evident, we only need dp[i - 1] to calculate dp[i]
        for (int j = i + 1; j <= n; j++) {
            if (diffarr[i] == diffarr[j] && j - i - 1 > dp[0][j-1]) {
                dp[1][j] = dp[0][j-1] + 1;
                ans = max(ans, dp[1][j]);
            }
            else 
                dp[1][j] = 0;
        }
        for (int j = 0; j <= n; j++)
            dp[0][j] = dp[1][j];
    }

    if (ans >= 4)
        printf("%d\n", ans + 1);
    else 
        printf("%d\n", 0);

    return 0;
}