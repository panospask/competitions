#include <bits/stdc++.h>

using namespace std;

int n, m, r;

// dp[i][j][k]: 1 if can reach (i, j) at time t=k
vector<vector<vector<bool>>> dp;

vector<vector<vector<bool>>> gun;

void solve(void)
{
    dp.clear();
    gun.clear();

    scanf("%d %d %d", &n, &m, &r);

    int maxt = n + m + r + 5;
    dp.assign(n + 1, vector<vector<bool>>(m + 1, vector<bool>(maxt, 0)));
    gun.assign(n + 1, vector<vector<bool>>(m + 1, vector<bool>(maxt, false)));

    for (int g = 0; g < r; g++) {
        int t, d, c;
        scanf("%d %d %d", &t, &d, &c);

        if (t < maxt) {
            // Fix this
            if (d == 1) {
                for (int j = 0; j <= m; j++)
                    gun[c][j][t] = true;
            }
            else {
                for (int i = 0; i <= n; i++)
                    gun[i][c][t] = true;
            }
        }
    }

    dp[0][0][0] = true;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k < maxt; k++) {
                if (!dp[i][j][k] || gun[i][j][k])
                    continue;

                if (k == maxt - 1)
                    continue;

                dp[i][j][k + 1] = true;

                if (i != n)
                    dp[i + 1][j][k + 1] = true;
                if (j != m)
                    dp[i][j + 1][k + 1] = true;
            }

    int ans = -1;
    for (int k = 0; k < maxt; k++)
        if (dp[n][m][k] && !gun[n][m][k]) {
            ans = k;
            break;
        }

    printf("%d\n", ans);
    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}