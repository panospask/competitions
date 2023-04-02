#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100
#define MAXK 7

using namespace std;

// dp[i][j][k]: Minimum steps needed to fill up first i spaces with j unlocks, the last happening at k
long long int dp[MAXN + 2][MAXK + 2][MAXN + 2];
int n, u;

long long int a[MAXN + 2];

void rot_array(void)
{
    int temp = a[0];

    for (int i = 0; i < n - 1; i++)
        a[i] = a[i+1];
    a[n-1] = temp;

    return;
}

long long int calc_ans(void)
{
    int ch = u - 1; // We have already unlocked the first door

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= ch; j++)
            for (int k = 0; k < n; k++)
                dp[i][j][k] = LONG_LONG_MAX;

    dp[0][0][0] = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j <= ch; j++)   
            for (int k = 0; k <= i; k++) {
                if (dp[i][j][k] == LONG_LONG_MAX)
                    continue;

                // Add the next room without opening new door
                dp[i+1][j][k] = min(dp[i+1][j][k], dp[i][j][k] + a[i+1] * (i+1-k));

                // Open a new door at the next room
                if (j < ch) {
                    dp[i+1][j+1][i+1] = min(dp[i+1][j+1][i+1], dp[i][j][k]);
                }
            }

    long long int ans = LONG_LONG_MAX;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[n-1][ch][i]);
    }

    return ans;
}

int main(void)
{
    freopen("cbarn2.in", "r", stdin);
    freopen("cbarn2.out", "w", stdout);

    scanf("%d %d", &n, &u);
    for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);

    long long int ans = LONG_LONG_MAX; 
    for (int i = 0; i < n; i++) {
        ans = min(ans, calc_ans());
        rot_array();
    }

    printf("%lld\n", ans);
    return 0;
}