#include <bits/stdc++.h>
#include <cassert>
#define pb push_back

using namespace std;

const int MOD = 998244353;
typedef long long ll;

int N;
vector<vector<int>> adj_list;
vector<int> subtree;
int maxleaf = 0;

vector<ll> total;
vector<ll> times;

void dfs(int node, int par) {
    subtree[node] = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        subtree[node] = max(subtree[node], max(neigh, subtree[neigh]));
    }
}

ll sumall(int node, int par, int t) {
    ll res = 0;
    if (node > t) {
        res += times[node];
    }

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        res = (res + sumall(neigh, node, t)) % MOD;
    }
    return res;
}

void solve(void) {
    scanf("%d", &N);

    maxleaf = 0;
    subtree.assign(N, 0);
    total.assign(N, 0);
    times.assign(N, 0);
    adj_list.assign(N, vector<int>());
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    for (int i = 0; i < N; i++) {
        if (adj_list[i].size() == 1) {
            maxleaf = i;
        }
    }
    if (maxleaf == N - 1) {
        printf("1\n");
        return;
    }

    dfs(N - 1, -1);

    for (int i = maxleaf; i < N - 1; i++) {
        if (subtree[i] > i) {
            // Nothing useful here
            total[i] = total[i - 1];
            continue;
        }
        if (i == maxleaf) {
            total[i] = times[i] = 1;
            continue;
        }

        times[i] = (total[i - 1] - total[subtree[i]] + MOD) % MOD;
        total[i] = (times[i] + total[i - 1]) % MOD;
    }

    int secbest = 0;
    for (auto kid : adj_list[N - 1]) {
        if (max(kid, subtree[kid]) == N - 2) {
            continue;
        }
        secbest = max(secbest, max(kid, subtree[kid]));
    }
    ll ans = (total[N - 2] - total[secbest] + MOD) % MOD;

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}