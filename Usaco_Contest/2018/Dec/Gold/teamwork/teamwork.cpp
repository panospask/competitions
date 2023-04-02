#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN (int)1e4
#define MAXK (int)1e3

using namespace std;

// dp[i][j]: Optimal solution if the latest used cow is i and there are j cows in the team 
long long int dp[MAXN + 2][MAXK + 2];
int highest_cow[MAXN + 2][MAXK + 2];
int team_size[MAXN + 2][MAXK + 2];
int n, k;
int skill[MAXN + 2];

int main(void)
{
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);

    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++)
        scanf("%d", &skill[i]);
    
    for (int i = 0; i <= k; i++) {
        highest_cow[0][i] = 0;
    }

    memset(dp, -1, sizeof(dp));
    dp[0][k] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            if (dp[i][j] == -1)
                continue;

            // Add the next cow in the team
            int newskill = skill[i+1];
            if (j != k) {
                highest_cow[i+1][j+1] = max(highest_cow[i][j], newskill);
                dp[i+1][j+1] = dp[i][j] + (long long int)(j + 1) * highest_cow[i+1][j+1] - (long long int)j * highest_cow[i][j]; 
            }

            // Create a new team
            highest_cow[i+1][1] = newskill;
            dp[i+1][1] = max(dp[i+1][1], dp[i][j] + newskill);
        }
    }

    long long int ans = 0;
    for (int j = 1; j <= k; j++)
        ans = max(ans, dp[n][j]);

    printf("%lld\n", ans);
    return 0;
}