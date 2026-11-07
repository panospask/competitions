#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

int N, K;

/* Key note: The smallest appearing element will always be on the side */

// dp[l][i]: Number of ways to build a wall of length l, with **smallest appearing element** i
vector<vector<ll>> dp;

// suff[l][i]: Suffix sum of dp for all j>=i with same parity as i (i, i+2, i+4, ...)
vector<vector<ll>> suff;

void calculate_suffix(int l) {
    suff[l][N] = dp[l][N];
    suff[l][N - 1] = dp[l][N - 1];
    for (int i = N - 2; i >= 0; i--) {
        suff[l][i] = (suff[l][i + 2] + dp[l][i]) % MOD;
    }
}

int main(void) {
    scanf("%d %d", &N, &K);

    dp.resize(K + 1, vector<ll>(N + 1, 0));
    suff.resize(K + 1, vector<ll>(N + 1, 0));
    dp[1][N] = 1;

    ll ans = 0;

    for (int l = 2; l <= K; l++) {
        calculate_suffix(l - 1);
        for (int i = 1; i < N; i++) {
            if (l == 2 && i != N - 1) {
                // When we have 2 elements and leave one we cannot do the left-right trick
                // to go wherever. We must go from i to i + 1 exactly, and only N has a value in l == 1
                continue;
            }
            // Assume I have i on one side
            // Then the next smallest appearing is either (i+1+2c) next to it
            dp[l][i] = suff[l - 1][i + 1];
            // Or on the opposite side
            int appear = i + (l - 1);
            if (l > 2 && appear <= N) {
                dp[l][i] = (dp[l][i] + suff[l - 1][appear]) % MOD;
            }

            // The sequence can be flipped and shifted 
            ll res = 2 * (K - l + 1) * dp[l][i];
            ans = (ans + res) % MOD;
        }
    }

    printf("%lld\n", ans);
    return 0;
}