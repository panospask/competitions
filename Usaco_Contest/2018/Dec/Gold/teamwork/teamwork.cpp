#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN (int)1e4
#define MAXK (int)1e3

using namespace std;

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
        dp[0][i] = 0;
        highest_cow[0][i] = 0;
        team_size[0][i] = 0;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++) {
            // Add the current cow on the team
            int mcow = max(highest_cow[i-1][j], skill[i]);
            int teamsz = team_size[i-1][j] + 1;
            long long int val = teamsz * mcow;

            dp[i][j] = val;
            highest_cow[i][j] = mcow;
            team_size[i][j] = teamsz;

            // Check if cutting out the team and forming new one is better
            if (dp[i][j] < dp[i-1][j-1] + skill[i]);

            // Finish later
        }
}