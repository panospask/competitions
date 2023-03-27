#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000
#define BUFFER 1e14

using namespace std;

typedef pair<int, int> ii;

ii operator + (ii a, ii b)
{
    return mp(a.first + b.first, a.second + b.second);
}

// dp[i][j]: The minimum energy needed to reach i in fj path and j in bessie path
// current time step NOT INCLUDED
long long int dp[MAXN + 2][MAXN + 2];

ii fj_path[MAXN + 2];
ii bessie_path[MAXN + 2];
int n, m;

long long int sq_dist(ii a, ii b)
{
    return (long long int)(a.first - b.first) * (a.first - b.first) + (long long int)(a.second - b.second) * (a.second - b.second);
}

int main(void)
{
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);

    scanf("%d %d", &n, &m);

    scanf("%d %d %d %d", &fj_path[0].first, &fj_path[0].second, &bessie_path[0].first, &bessie_path[0].second);
    getchar();

    for (int i = 1; i <= n; i++) {
        char c = getchar();
        if (c == 'N')
            fj_path[i] = fj_path[i-1] + mp(0, 1);
        else if (c == 'S')
            fj_path[i] = fj_path[i-1] + mp(0, -1);
        else if (c == 'E')
            fj_path[i] = fj_path[i-1] + mp(1, 0);
        else 
            fj_path[i] = fj_path[i-1] + mp(-1, 0);
    }

    getchar();
    for (int i = 1; i <= m; i++) {
        char c = getchar();
        if (c == 'N')
            bessie_path[i] = bessie_path[i-1] + mp(0, 1);
        else if (c == 'S')
            bessie_path[i] = bessie_path[i-1] + mp(0, -1);
        else if (c == 'E')
            bessie_path[i] = bessie_path[i-1] + mp(1, 0);
        else 
            bessie_path[i] = bessie_path[i-1] + mp(-1, 0);
    }

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++) 
            dp[i][j] = BUFFER;

    dp[0][0] = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++) {

            if (dp[i][j] == BUFFER)
                continue;

            long long int cur_consume;
            if (i == 0 && j == 0)
                cur_consume = 0;
            else {
                cur_consume = sq_dist(fj_path[i], bessie_path[j]);
            }

            // Move only fj forward
            if (i != n) {
                dp[i+1][j] = min(dp[i+1][j], dp[i][j] + cur_consume);
            }
            // Move only bessie forward
            if (j != m) {
                dp[i][j+1] = min(dp[i][j+1], dp[i][j] + cur_consume);
            }
            // Move both forward
            if (i != n && j != m) {
                dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + cur_consume);
            }
        }

    long long int ans = dp[n][m] + sq_dist(fj_path[n], bessie_path[m]);

    printf("%lld\n", ans);
    return 0;
}