/*
ID: panos.p1
LANG: C++11
TASK: inflate
*/

#include <bits/stdc++.h>
#define MAXN 10000

using namespace std;

int dp[MAXN + 5];
int mins[MAXN + 5];
int val[MAXN + 5];
int ttl_time, n;

int main(void)
{
    freopen("inflate.in", "r", stdin);
    freopen("inflate.out", "w", stdout);

    scanf("%d %d", &ttl_time, &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &val[i], &mins[i]);

    dp[0] = 0;
    for (int i = 0; i < n; i++)
        for (int j = mins[i]; j <= ttl_time; j++)
            dp[j] = max(dp[j], dp[j - mins[i]] + val[i]);


    for (int i = 1; i < ttl_time; i++)
        dp[ttl_time] = max(dp[i], dp[ttl_time]);
    printf("%d\n", dp[ttl_time]);
    return 0;
}