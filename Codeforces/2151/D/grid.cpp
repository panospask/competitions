#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

typedef long long ll;

int N;
vector<ll> fact;
vector<ll> inv;
vector<int> A;

ll calc_pow(ll a, int b) {
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

void pracalculate(void) {
    fact.resize(N + 1);
    inv.resize(N + 1);

    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    inv[N] = calc_pow(fact[N], MOD - 2);
    for (int i = N - 1; i >= 0; i--) {
        inv[i] = (i + 1) * inv[i + 1] % MOD;
    }
}

ll choose(int a, int b) {
    if (b < 0 || b > a) {
        return 0;
    }

    ll nom = fact[a];
    ll den = inv[a - b] * inv[b] % MOD;

    return nom * den % MOD;
}

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    pracalculate();
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int cut = (N + 1) / 2;

    for (int i = cut; i < N; i++) {
        if (A[i]) {
            printf("0\n");
            return;
        }
    }

    ll ways = 1;
    int prv = 0;
    for (int i = cut - 1; i >= 0; i--) {
        int need = 2;
        if ((N % 2) && i == cut - 1) {
            need = 1;
        }

        if (A[i] > prv + need) {
            // Cannot fullfill
            ways = 0;
        }

        // Way to choose which positions to keep
        ways = ways * choose(prv + need, A[i]) % MOD;
        prv = prv + need - A[i];
    }

    if (prv) {
        ways = 0;
    }

    printf("%lld\n", ways);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}