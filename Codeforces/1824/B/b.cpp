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
    subtree[node] = 1;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        subtree[node] += subtree[neigh];
    }

    // The total configurations in which the edge from this node to parent is an edge between
    // 2 good nodes
    ll total = choose(subtree[node], K / 2) * choose(N - subtree[node], K / 2) % MOD;
    add(ans, total);
}

int main(void) {
    scanf("%d %d", &N, &K);

    precalculate();
    subtree.resize(N);
    adj_list.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    if (K % 2 == 1) {
        printf("1\n");
        return 0;
    }

    dfs(0, -1);
    ans = ans * calc_inv(choose(N, K)) % MOD;

    // Answer is 1 good node + Expected amount of edges
    add(ans, 1);

    printf("%lld\n", ans);
}