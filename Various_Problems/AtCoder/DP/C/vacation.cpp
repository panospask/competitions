#include <bits/stdc++.h>

using namespace std;

const int TOTAL = 3;

int N;
vector<vector<int>> activities;
vector<vector<int>> dp;

int main(void)
{
    scanf("%d", &N);

    activities.resize(N + 1, vector<int>(TOTAL));
    dp.resize(N + 1, vector<int>(TOTAL));

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < TOTAL; j++) {
            scanf("%d", &activities[i][j]);
        }
    }

    dp[0].assign(TOTAL, 0);
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < TOTAL; j++) {
            dp[i][j] = 0;
            for (int k = 0; k < TOTAL; k++) {
                if (k == j)
                    continue;

                dp[i][j] = max(dp[i][j], dp[i - 1][k] + activities[i][j]);
            }
        }
    }

    int ans = 0;
    for (int j = 0; j < TOTAL; j++)
        ans = max(ans, dp[N][j]);

    printf("%d\n", ans);

    return 0;
}