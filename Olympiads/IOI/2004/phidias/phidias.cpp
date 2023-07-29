#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e6;

int N, H, W;

vector<pi> slabs;
vector<vector<int>> dp;

int main(void)
{
    scanf("%d %d %d", &W, &H, &N);

    slabs.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &slabs[i].f, &slabs[i].s);
    }

    dp.assign(W + 1, vector<int>(H + 1, 0));

    for (int i = 1; i <= W; i++) {
        for (int j = 1; j <= H; j++) {
            dp[i][j] = INF;
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + j);
            dp[i][j] = min(dp[i][j], dp[i][j - 1] + i);

            for (int v = 0; v < N; v++) {
                int n_i = i - slabs[v].f;
                int n_j = j - slabs[v].s;

                if (n_i < 0 || n_j < 0)
                    continue;

                dp[i][j] = min(dp[i][j], dp[n_i][j] + dp[slabs[v].f][n_j]);
                dp[i][j] = min(dp[i][j], dp[n_i][slabs[v].s] + dp[i][n_j]);
            }
        }
    }

    printf("%d\n", dp[W][H]);

    return 0;
}