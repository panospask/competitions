#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXT = 60;
const int MOD = (int)1e9 + 7;

int N;
ll K;
vector<vector<int>> a;
// dp[l][i][j]: Paths of length 2^l that start at i and end at j
vector<vector<ll>> dp[MAXT];

vector<vector<ll>> ans, prv;

int main(void)
{
    scanf("%d %lld", &N, &K);

    a.resize(N, vector<int>(N));
    dp[0].assign(N, vector<ll>(N, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            scanf("%d", &a[i][j]);
            dp[0][i][j] = a[i][j];
        }

    prv.assign(N, vector<ll>(N, 0));
    ans.assign(N, vector<ll>(N, 0));
    for (int i = 0; i < N; i++)
        prv[i][i] = 1;
    if (K % 2) {
        K--;
        prv = dp[0];
    }

    for (int l = 1; (1ll << l) <= K; l++) {
        dp[l].assign(N, vector<ll>(N, 0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // Calculate dp[l][i][j]
                dp[l][i][j] = 0;

                for (int k = 0; k < N; k++) {
                    dp[l][i][j] += dp[l - 1][i][k] * dp[l - 1][k][j] % MOD;
                }
                dp[l][i][j] %= MOD;
            }
        }

        if (K & (1ll << l)) {
            // Add 2^l to the already calculated length
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++) {
                    ans[i][j] = 0;
                    for (int k = 0; k < N; k++)
                        ans[i][j] += prv[i][k] * dp[l][k][j] % MOD;
                    ans[i][j] %= MOD;
                }

            swap(ans, prv);
        }
    }

    ll tot = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tot += prv[i][j];

    tot %= MOD;

    printf("%lld\n", tot);

    return 0;
}