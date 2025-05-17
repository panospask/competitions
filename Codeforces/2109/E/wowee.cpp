#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

int N, K;
vector<vector<vector<ll>>> dp;
vector<int> s;

void solve(void) {
    scanf("%d %d", &N, &K);

    s.resize(N);
    dp.assign(N + 1, vector<vector<ll>>(K + 1, vector<ll>(2, 0)));

    for (int i = 0; i < N; i++) {
        scanf("%1d", &s[i]);
    }

    dp[0][0][0] = dp[0][0][1] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            for (int f = 0; f <= 1; f++) {
                // Find ways to perform j operations in the first i positions, f if flipped from before

                dp[i][j][f] = 0;

                // Do nothing in position i
                dp[i][j][f] = dp[i - 1][j][f];
                
                if (f ^ s[i - 1] == 0) {
                    // Do some flips before position i, flip in i, some flips after i
                    for (int bef = 0; bef < j; bef++) {
                        dp[i][j][f] += dp[i - 1][bef][f] * 1 * dp[i - 1][j - bef - 1][!f] % MOD;
                        dp[i][j][f] %= MOD;
                    }
                }
            }
        }
    }

    printf("%lld\n", dp[N][K][0]);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}