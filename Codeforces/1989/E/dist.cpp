#include <bits/stdc++.h>
#define MOD(var) ((var) = ((var) % MOD + MOD) % MOD)

using namespace std;

typedef long long ll;

const int MOD = 998244353;

int N, K;

// dp[i][j]: Number of ways to split the first i elements into j blocks (or more than j if j == K)
// Blocks of length 2 are only allowed when i == 2 or i == N
vector<vector<ll>> dp;
vector<vector<ll>> pref;

int main(void)
{
    scanf("%d %d", &N, &K);

    dp.assign(N + 1, vector<ll>(K + 1, 0));
    pref.assign(N + 1, vector<ll>(K + 1, 0));

    dp[0][0] = 1;
    pref[0][0] = dp[0][0];

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][min(j + 1, K)] += pref[i - 1][j];
            if (i > 2 && i != N) {
                dp[i][min(j + 1, K)] -= dp[i - 2][j];
            }
            MOD(dp[i][min(j + 1, K)]);
        }

        for (int j = 0; j <= K; j++) {
            pref[i][j] = pref[i - 1][j] + dp[i][j];
        }
    }

    printf("%lld\n", dp[N][K]);

    return 0;
}