#include <bits/stdc++.h>

using namespace std;

int N;
// dp[i][j]: Probability of j coins after i tosses
vector<vector<double>> dp;
vector<double> p;

int main(void)
{
    scanf("%d", &N);

    p.resize(N + 1);
    dp.resize(N + 1, vector<double>(N + 1, 0));

    for (int i = 1; i <= N; i++)
        scanf("%lf", &p[i]);

    dp[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        dp[i][0] = dp[i - 1][0] * (1 - p[i]);
        for (int j = 1; j <= N; j++)
            dp[i][j] = dp[i - 1][j] * (1 - p[i]) + dp[i - 1][j - 1] * p[i];
    }

    double ans = 0;
    for (int j = N / 2 + 1; j <= N; j++)
        ans += dp[N][j];

    printf("%.10lf\n", ans);

    return 0;
}