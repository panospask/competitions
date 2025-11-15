#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

int N;
vector<vector<ll>> dp;

ll calc_pow(ll a, int b) {
    ll c = 1;

    while (b) {
        if (b & 1) {
            c = c * a % MOD;
        }

        b /= 2;
        a = a * a % MOD;
    }

    return c;
}

ll find_inv(ll a) {
    return calc_pow(a, MOD - 2);
}

void solve(void) {
    scanf("%d", &N);

    dp.assign(N, vector<ll>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            ;
        }
    }
}