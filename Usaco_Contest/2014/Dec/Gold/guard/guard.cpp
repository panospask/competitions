#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 20
#define MAXH ((int)1e9)
#define CHECK_BIT(var, pos) (var & (1<<pos))

using namespace std;

//dp[i] is the maximum safety factor for the set consisting of the values with bit rep 1
long long int dp[(1<<MAXN)];
int n, h;
long long int height_total[(1<<MAXN)];
int strength[MAXN + 2];
int weight[MAXN + 2];
int height[MAXN + 2];

int main(void)
{
    freopen("guard.in", "r", stdin);
    freopen("guard.out", "w", stdout);

    scanf("%d %d", &n, &h);
    for (int i = 0; i < n; i++)
        scanf("%d %d %d", &height[i], &weight[i], &strength[i]);

    memset(dp, -1, sizeof(dp));
    dp[0] = LONG_LONG_MAX; // It's the floor, place whatever you want
    height_total[0] = 0;

    long long int ans = -1;
    for (int s = 0; s < (1<<n); s++) {
        if (dp[s] < 0)
            continue;

        if (height_total[s] >= h) {
            // No use putting another cow in the stack
            ans = max(ans, dp[s]);
            continue;
        }

        for (int i = 0; i < n; i++) {
            if (!CHECK_BIT(s, i)) {
                // Put the cow in the stack
                long long int minv = min(dp[s] - weight[i], (long long int)strength[i]);

                dp[s + (1<<i)] = max(dp[s + (1<<i)], minv);
                height_total[s + (1<<i)] = height_total[s] + height[i];
            }
        }
    }

    if (ans == -1)
        printf("Mark is too tall\n");
    else 
        printf("%lld\n", ans);

    return 0;
}