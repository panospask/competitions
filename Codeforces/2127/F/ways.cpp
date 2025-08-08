#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

int N, M;
vector<ll> fact;
vector<ll> inv;

ll calc_pow(ll a, ll b) {
    ll c = 1;
    while (b) {
        if (b % 2) {
            c = c * a % MOD;
        }

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

void calculate_factorials(void) {
    fact[0] = 1;
    
    for (int i = 1; i < N + M; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv[N + M - 1] = calc_pow(fact[N + M - 1], MOD - 2);
    for (int i = N + M - 2; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

ll choose(ll a, ll b) {
    if (b < 0 || b > a) {
        return 0;
    }

    ll nom = fact[a];
    ll den = inv[a - b] * inv[b] % MOD;

    return nom * den % MOD;
}

// Total number of arrays length N, sum M, elements <= X
ll g(int N, int M, int X) {
    ll ans = 0;
    int sign = 1;
    // Make X a strict bound
    X++;

    for (int k = 0; k * X <= M; k++) {
        ll add = sign * choose(N, k) * choose(M - k * X + N - 1, M - k * X) % MOD;
        if (add < 0) {
            add += MOD;
        }
        sign = -sign;

        ans = (ans + add) % MOD;
    }

    return ans;
}

void solve(void) {
    scanf("%d %d", &N, &M);

    ll ans = 0;
    for (int v = M; v > 0; v--) {
        ll maximums = g(N - 1, M - v, v) + (N - 1) * g(N - 2, M - 2 * v, v) % MOD;
        maximums %= MOD;
        maximums = maximums * v % MOD;

        ll onepos = (M - v) * g(N - 1, M - v, v) % MOD * calc_pow(N - 1, MOD - 2) % MOD;
        ll aftermax = (M - 2 * v) * g(N - 2, M - 2 * v, v) % MOD;
        aftermax = (aftermax + v * g(N - 2, M - 2 * v, v)) % MOD;

        ans = (ans + maximums - onepos - aftermax) % MOD;
        ans = (ans + MOD) % MOD;
    }

    printf("%lld\n", ans);
}

int main(void) {
    N = 2e5;
    M = 2e5;
    fact.resize(N + M);
    inv.resize(N + M);
    calculate_factorials();

    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}