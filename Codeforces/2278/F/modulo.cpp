#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

int N, M;

// How many ways to use the first i places, with the last having value j
vector<vector<ll>> dp;

vector<vector<ll>> modify;

void add(ll& a, ll b) {
    a += b;
    a = (a % MOD + MOD) % MOD;
}

void solve(void) {
    scanf("%d %d", &N, &M);

    dp.assign(N + 2, vector<ll>(M + 3, 0));
    modify.assign(N + 2, vector<ll>(M + 4, 0));
    // We can assume we have an (N+1)-value of 1
    dp[0][1] = 1;
    for (int i = 0; i <= N; i++) {
        ll cur = 0;
        for (int v = 1; v <= M + 2; v++) {
            // Apply modifications
            add(cur, modify[i][v]);
            add(dp[i][v], cur);

            // We can create a new player with values in [v, 2v)
            int l = v;
            int r = min(2 * v, M + 3);
            if (r == 2) {
                r++;
            }

            add(modify[i + 1][l], dp[i][v]);
            add(modify[i + 1][r], -dp[i][v]);
        }
    }

    printf("%lld\n", dp[N][M + 2]);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}