/*
ID: panos.p1
LANG: C++11
TASK: stamps
*/

#include <bits/stdc++.h>
#define MAXN 50
#define MAXK 200

using namespace std;

int dp[10000 * MAXK + 5];
int n, k;
int stamps[MAXK];

int main(void)
{
    freopen("stamps.in", "r", stdin);
    freopen("stamps.out", "w", stdout);

    scanf("%d %d", &k, &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &stamps[i]);
    sort(stamps, stamps + n);
    int maxval = stamps[n-1] * k;
    
    for (int i = 0; i <= maxval; i++)
        dp[i] = 10e8;

    dp[0] = 0;
    for (int i = 0; i < n; i++)
        for (int j = stamps[i]; j <= maxval; j++) {
            dp[j] = min(dp[j], dp[j - stamps[i]] + 1);
        }

    int cnt = 0;
    for (int i = 1; i <= maxval && dp[i] <= k; i++)
        cnt++;

    printf("%d\n", cnt);
    return 0;
}