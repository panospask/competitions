#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

int N;
ll ans;

vector<vector<int>> par;
vector<vector<int>> graph;

// Number of flight routes between i and j
vector<vector<int>> dp;

int main(void)
{
    scanf("%d", &N);

    par.resize(N, vector<int>(N));
    graph.assign(N, vector<int>(N, false));
    dp.resize(N, vector<int>(N));
    ans = 0;

    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            scanf("%1d", &par[i][j]);

    for (int len = 2; len <= N; len++) {
        for (int l = 0; l + len <= N; l++) {
            int r = l + len - 1;

            // Calculate number of flight routes between l and r
            dp[l][r] = 0;
            for (int i = l + 1; i < r; i++) {
                if (graph[l][i]) {
                    dp[l][r] += dp[i][r];
                }
            }
            dp[l][r] %= 2;

            if (dp[l][r] != par[l][r]) {
                // There is direct flight between l and r
                dp[l][r]++;
                dp[l][r] %= 2;
                graph[l][r] = true;
                ans++;
            }
        }
    }

    printf("%lld\n", ans);

    return 0;
}