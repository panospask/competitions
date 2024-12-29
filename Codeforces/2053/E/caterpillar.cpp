#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
int leafs;
ll ans = 0;
vector<vector<int>> adj_list;

vector<bool> isleaf;
vector<bool> adjacent;

// dp[node]: Number of nodes in the subtree of node s.t:
// They are NOT leafs and their parent is adjacent to a leaf
vector<int> dp;


// isleaf and adjacent should already be worked out
void dfs(int node, int par)
{
    dp[node] = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);

        dp[node] += dp[neigh];
    }

    if (!adjacent[node]) {
        // If we place the head at node, and the tail at a node with parent adjacent to leaf
        // Then Aron wins

        ans += dp[node];
    }
    dp[node] += par != -1 && adjacent[par] && !isleaf[node];
}

void reroot(int node, int par, int v)
{
    if (!adjacent[node]) {
        ans += v;
    }

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        int cnt = v + dp[node] - dp[neigh];
        // The new "parent" of node is not par, it is the current neighbour
        cnt -= par != -1 && adjacent[par] && !isleaf[node];
        cnt += adjacent[neigh] && !isleaf[node];

        reroot(neigh, node, cnt);
    }
}

void solve(void)
{
    scanf("%d", &N);

    adj_list.assign(N, vector<int>());
    adjacent.assign(N, false);
    isleaf.assign(N, false);
    dp.assign(N, 0);
    leafs = 0;
    ans = 0;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    for (int i = 0; i < N; i++) {
        isleaf[i] = adj_list[i].size() == 1;
        leafs += isleaf[i];
    }
    for (int i = 0; i < N; i++) {
        adjacent[i] = isleaf[i];
        for (auto v : adj_list[i]) {
            adjacent[i] = adjacent[i] || isleaf[v];
        }
    }

    dfs(0, -1);
    reroot(0, -1, 0);

    ans += (ll)leafs * (N - leafs);

    printf("%lld\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}