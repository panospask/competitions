#include <bits/stdc++.h>
#define MOD (1000000007)

using namespace std;

typedef long long ll;

int n, m, q;
vector<vector<int>> adj_list;
vector<int> componentnum;
vector<int> comp_par;
vector<bool> is_cycle;
vector<int> p;
vector<int> depth;
vector<vector<int>> ancestors;
vector<vector<ll>> v;
int total_comps = 0;

void dfs(int node, int par, int d)
{
    p[node] = par;
    depth[node] = d;

    // Focus on finding the back edge first (if exists)
    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;

        else if (depth[neigh] != -1 && depth[neigh] < depth[node]) {
            // New cycle found
            componentnum[node] = total_comps++;
            is_cycle.push_back(true);
            for (int i = p[node]; i != neigh; i = p[i]) {
                componentnum[i] = componentnum[node];
            }
            componentnum[neigh] = componentnum[node];
            comp_par[total_comps - 1] = neigh;
        }
    }

    for (auto neigh : adj_list[node]) {
        if (depth[neigh] == -1) {
            dfs(neigh, node, d + 1);
        }
    }

}

void dfs_components(int node, int par)
{
    depth[node] = depth[par] + 1;
    ancestors[0][node] = par;
    v[0][node] = {is_cycle[node] ? 2 : 1};

    for (auto neigh : adj_list[node])
        dfs_components(neigh, node);
}

pair<int, int> jump(int a, int levels)
{
    ll res = 1;
    int node = 0;
    for (int i = 0; i < 20; i++)
        if (levels & (1<<i)) {
            res = res * v[i][a] % MOD;
            a = ancestors[i][a];
        }

    return make_pair(a, res);
}

ll lcaval(int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b);

    ll in_v = 1;
    tie(a, in_v) = jump(a, depth[a] - depth[b]);
    // cout << in_v;

    if (a == b) {
        return in_v * v[0][a];
    }
    for (int i = 20 - 1; i >= 0; i--) {
        int oa = ancestors[i][a];
        int ob = ancestors[i][b];
        if (oa != ob) {
            in_v = (in_v * v[i][a] % MOD)* v[i][b] % MOD;
            a = oa;
            b = ob;
        }
    }

    ll ans = ((in_v * v[0][a]) % MOD * (v[0][b] * v[0][ancestors[0][a]]) % MOD) % MOD;
    return ans % MOD;
}

int main()
{
    scanf("%d %d", &n, &m);
    adj_list.resize(n);
    componentnum.assign(n + 1, -1);
    p.assign(n, -1);
    comp_par.resize(n + 1);
    depth.assign(n + 1, -1);
    componentnum[n] = n;
    ancestors.resize(20, vector<int>(n + 1));
    v.resize(20, vector<ll>(n + 1));

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    dfs(0, n, 0);

    for (int i = 0; i < n; i++) {
        if (componentnum[i] == -1) {
            componentnum[i] = total_comps++;
            is_cycle.push_back(false);
            comp_par[total_comps - 1] = i;
        }
    }

    adj_list.clear();
    adj_list.resize(total_comps);
    for (int i = 0; i < n; i++) {
        if (i == comp_par[componentnum[i]] && i != 0)
            adj_list[componentnum[p[i]]].push_back(componentnum[i]);
    }

    ancestors[0][total_comps] = total_comps;
    depth.assign(total_comps + 5, -1);
    dfs_components(componentnum[0], total_comps);


    for (int up = 1; up < 20; up++)
        for (int c= 0; c < total_comps; c++)  {
            ancestors[up][c] = ancestors[up - 1][ancestors[up - 1][c]];
            v[up][c] = v[up-1][ancestors[up-1][c]] * v[up-1][c] % MOD;
        }

    scanf("%d", &q);
    while (q--) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--;
        x = componentnum[x];
        y = componentnum[y];

        ll ans = lcaval(x, y) % MOD;
        printf("%lld\n", ans);
    }

    return 0;
}
