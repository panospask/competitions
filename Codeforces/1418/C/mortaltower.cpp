#include <bits/stdc++.h>

using namespace std;

const int BIG = 1e9;

int N;
vector<vector<int>> dp;
vector<int> hard;

void solve(void)
{
    scanf("%d", &N);

    dp.assign(N + 1, vector<int>(2, BIG));
    hard.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &hard[i]);
    }

    dp[0][1] = 0;
    for (int i = 0; i < N; i++) {
        for (int f = 0; f < 2; f++) {
            int s1 = hard[i] && f;
            dp[i + 1][!f] = min(dp[i + 1][!f], dp[i][f] + s1);

            if (i < N - 1) {
                int s2 = s1 + (hard[i + 1] && f);
                dp[i + 2][!f] = min(dp[i + 2][!f], dp[i][f] + s2);
            }
        }
    }

    printf("%d\n", min(dp[N][0], dp[N][1]));
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}