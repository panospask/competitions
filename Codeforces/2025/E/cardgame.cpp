#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MOD = 998244353;

int N, M;
vector<vector<ll>> c;

// dp[i][j]: Number of possible ways if we have considered the first i+1 suits and used(to our advantage) j cards of suit 1
vector<vector<ll>> dp;

void precalc(void)
{
    c.resize(2 * M + 1, vector<ll>(2 * M + 1));

    c[0][0] = 1;
    for (int i = 1; i <= 2 * M; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
        }
    }
}

int choose(int a, int b)
{
    if (b < 0 || b > a) {
        return 0;
    }

    return c[a][b];
}

// Compute dyck paths shifted by s
ll compute(int b)
{
    ll v = choose(2 * M, M + b) - choose(2 * M, M + b + 1);

    return (v % MOD + MOD) % MOD;
}

int main(void)
{
    scanf("%d %d", &N, &M);

    precalc();

    M = M / 2;
    dp.assign(N, vector<ll>(M + 1, 0));
    
    dp[0][0] = 1;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= M; j++) {
            // Calculate dp[i][j]

            for (int cur = 0; cur <= j; cur++) {
                // How many of the advantages we will currently use
                ll v = dp[i - 1][j - cur] * compute(cur) % MOD;

                dp[i][j] = (dp[i][j] + v) % MOD;
            }
        }
    }

    ll ans = 0;
    for (int j = 0; j <= M; j++) {
        ll v = dp[N - 1][j] * compute(j) % MOD;

        ans = (ans + v) % MOD;
    }

    printf("%lld\n", ans);
}