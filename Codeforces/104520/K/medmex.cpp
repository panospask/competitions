#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

const int MAXN = 1e5 + 1;

int N;
vector<ll> fact;
vector<ll> inv;

ll calc_power(ll a, int b) {
    ll c = 1;
    while (b) {
        if (b % 2) {
            c = c * a % MOD;
        }

        b /= 2;
        a = a * a % MOD;
    }

    return c;
}

ll choose(int a, int b) {
    if (b < 0 || b > a) {
        return 0;
    }

    ll nom = fact[a];
    ll den = inv[b] * inv[a - b] % MOD;

    return nom * den % MOD;
}

void solve(void) {
    scanf("%d", &N);

    ll ans = 0;
    printf("0 ");
    for (int med = 2; med <= N; med++) {
        int prvcnt = med - 1;
        int afterspots = N - med - 1;
        
        ll res = choose(afterspots, prvcnt - 1);
        if (res) {
            int total = 2 * prvcnt;
        
            res = res * fact[total] % MOD;
            res = res * fact[N - total] % MOD;
            res = res * (N - total + 1) % MOD;
        }
        printf("%lld ", res);
    }

    printf("\n");
}

void precalculate(void) {
    fact.resize(MAXN);
    inv.resize(MAXN);

    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv[MAXN - 1] = calc_power(fact[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    precalculate();
    while (t--) {
        solve();
    }
}