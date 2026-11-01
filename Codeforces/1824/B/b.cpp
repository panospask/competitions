#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

typedef long long ll;

int K, N;
vector<vector<int>> adj_list;
vector<int> subtree;

ll ans = 0;
vector<ll> fact;
vector<ll> inv;

void add(ll& a, ll b) {
    a += b;
    a = (a % MOD + MOD) % MOD;
}

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

ll calc_inv(ll a) {
    return calc_pow(a, MOD - 2);
}

ll choose(ll n, ll k) {
    if (k < 0 || k > n) {
        return 0;
    }

    ll nom = fact[n];
    ll den = inv[k] * inv[n - k] % MOD;
    return nom * den % MOD;
}

// Distribute a balls in b boxes
ll distribute(ll a, ll b) {
    return choose(a + b - 1, a);
}

void precalculate(void) {
    fact.assign(2 * N + 1, 0);
    inv.assign(2 * N + 1, 0);

    fact[0] = 1;
    for (int i = 1; i <= 2 * N; i++) {
        fact[i] = i * fact[i - 1] % MOD;
    }
    inv[2 * N] = calc_inv(fact[2 * N]);
    for (int i = 2 * N - 1; i >= 0; i--) {
        inv[i] = (i + 1) * inv[i + 1] % MOD;
    }
}

void dfs(int node, int par) {
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        subtree[node] += subtree[neigh];
    }

    add(ans, choose(N, K));
}

int main(void) {
    ;
}