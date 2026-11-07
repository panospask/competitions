#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

int N;
vector<vector<int>> adj_list;
vector<int> depth;
// Max depth in subtree
vector<int> subtree;

ll half = 1;
ll ans = 0;

void add(ll& a, ll b) {
    a = a + b;
    a %= MOD;
}

void dfs(int node, int par) {
    subtree[node] = depth[node];
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }
        depth[neigh] = depth[node] + 1;
        dfs(neigh, node);
        subtree[node] = max(subtree[node], subtree[neigh]);
    }

    add(ans, half * (subtree[node] - depth[node] + 1) % MOD);
}

void solve(void) {
    scanf("%d", &N);

    adj_list.assign(N, vector<int>());
    depth.assign(N, 0);
    subtree.assign(N, 0);
    ans = 0;
    half = 1;
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    for (int i = 0; i < N - 1; i++) {
        half = half * 2 % MOD;
    }
    
    depth[0] = 0;
    dfs(0, -1);

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}