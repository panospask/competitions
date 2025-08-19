#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

int N, M;
vector<int> cnt;
vector<int> A;
vector<ll> order;

vector<vector<ll>> dp;

int main(void) {
    scanf("%d %d", &N, &M);

    cnt.resize(1 << M);
    A.resize(N);
    order.resize(N + 1);

    for (int b = 0; b < M; b++) {
        for (int i = 0; i < N; i++) {
            char c;
            scanf(" %c", &c);
            if (c == 'H') {
                A[i] += (1 << b);
            }
        }
    }

    order[0] = 1;
    for (int i = 1; i <= N; i++) {
        order[i] = (i * order[i - 1] + 1) % MOD;
    }

    for (int i = 0; i < N; i++) {
        cnt[A[i]]++;
    }

    dp.resize(1 << M, vector<ll>(M, 0));

    // dp[mask][i]: Sum of dp[m] for submasks of mask that differ only in the first i bits
    ll ans = 0;
    for (int mask = 0; mask < (1 << M); mask++) {
        // Iterate over all submasks that differ by 1 bit and create results
        ll sum = 0;
        for (int b = 0; b < M; b++) {
            if (CHECK_BIT(mask, b)) {
                sum += dp[mask - (1 << b)][b];
            }
        }
        dp[mask][0] = (sum + 1) % MOD * (order[cnt[mask]] - 1) % MOD;
        ans = (ans + dp[mask][0]) % MOD;

        // Calculate the rest of dp[mask]
        for (int b = 0; b < M - 1; b++) {
            dp[mask][b + 1] = dp[mask][b];
            if (CHECK_BIT(mask, b)) {
                dp[mask][b + 1] += dp[mask - (1 << b)][b];
            }
            dp[mask][b + 1] %= MOD;
        }
    }

    printf("%lld\n", ans);

    return 0;
}