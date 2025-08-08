#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

int N, M;
vector<vector<int>> adj_list;
vector<bool> visited;
vector<ll> fact;

ll dfs(int node, int par) {
    if (visited[node]) {
        return 0;
    }

    visited[node] = true;
    ll ways = 1;
    int leafs = 0;
    int nonleafs = (par != -1);
    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            ll res = dfs(neigh, node);
            ways = ways * res % MOD;
            
            if (adj_list[neigh].size() == 1) {
                leafs++;
            }
            else {
                nonleafs++;
            }
        }
    }

    if (nonleafs > 2) {
        return 0;
    }
    if (par == -1 && nonleafs > 0) {
        ways = ways * 2 % MOD;
    }
    ways = ways * fact[leafs] % MOD;

    return ways;
}

void solve(void) {
    scanf("%d %d", &N, &M);

    adj_list.clear();
    adj_list.resize(N);
    fact.resize(N);
    visited.assign(N, false);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    int u = 0;
    while (N > 2 && adj_list[u].size() == 1) {
        u++;
    }
    
    ll ans = dfs(u, -1);
    ans = ans * 2 % MOD;

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}