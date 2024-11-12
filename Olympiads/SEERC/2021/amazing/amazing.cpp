#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int INF = 1e6;

int N;
vector<vector<int>> adj_list;
vector<int> leafs;
vector<int> dep;

vector<int> ans;

bool leafsort(int a, int b)
{
    if (leafs[a] == leafs[b]) {
        return dep[a] < dep[b];
    }

    return leafs[a] < leafs[b];
}

void dfs(int node, int par)
{
    dep[node] = par == -1 ? 0 : dep[par] + 1;
    leafs[node] = N;
    if (adj_list[node].size() == 1 && par != -1) {
        leafs[node] = node;
    }

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        leafs[node] = min(leafs[node], leafs[neigh]);
    }
}

int reroot(int node, int par)
{
    sort(adj_list[node].begin(), adj_list[node].end(), leafsort);

    if (adj_list[node].size() == 1 && par != -1) {
        return node;
    }

    int u = adj_list[node].back();
    assert(u != par);

    if (leafs[u] > node) {
        return reroot(u, node);
    }

    return node;
}

void calculate(int node, int par)
{
    sort(adj_list[node].begin(), adj_list[node].end(), leafsort);

    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            calculate(neigh, node);
        }
    }

    ans.pb(node);
}

void solve(void)
{
    scanf("%d", &N);

    adj_list.assign(N, vector<int>());
    leafs.resize(N);
    dep.resize(N);
    ans.clear();

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    int r1 = N;
    for (int i = 0; i < N; i++) {
        if (adj_list[i].size() == 1) {
            r1 = min(r1, i);
        }
    }

    dfs(r1, -1);
    int r2 = reroot(r1, -1);
    dfs(r2, -1);
    calculate(r2, -1);

    for (int i = 0; i < N; i++) {
        printf("%d ", ans[i] + 1);
    }
    printf("\n");

    return;
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