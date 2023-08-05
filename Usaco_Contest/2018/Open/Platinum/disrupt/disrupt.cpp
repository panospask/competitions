#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

const int MAXLOG = 17;

typedef pair<int, int> pi;

int N, M;

vector<vector<int>> adj_list;
vector<int> ancestor[MAXLOG];
vector<multiset<int>> active;
vector<vector<int>> starting;
vector<vector<int>> ending;
map<pi, int> edges;
vector<int> dep;
vector<int> ans;

int jump(int a, int lvl)
{
    for (int i = MAXLOG - 1; i >= 0; i--)
        if (lvl & (1 << i))
            a = ancestor[i][a];

    return a;
}

int lca(int a, int b)
{
    if (dep[a] < dep[b])
        swap(a, b);

    a = jump(a, dep[a] - dep[b]);
    if (a == b)
        return a;

    for (int up = MAXLOG - 1; up >= 0; up--) {
        if (ancestor[up][a] != ancestor[up][b]) {
            a = ancestor[up][a];
            b = ancestor[up][b];
        }
    }

    return ancestor[0][a];
}

void dfs(int node, int d)
{
    dep[node] = d;

    for (auto neigh : adj_list[node])
        if (neigh != ancestor[0][node]) {
            ancestor[0][neigh] = node;
            dfs(neigh, d + 1);
        }
}

void getans(int node)
{
    for (auto neigh : adj_list[node]) {
        if (neigh == ancestor[0][node])
            continue;

        getans(neigh);
        if (active[neigh].size() > active[node].size())
            swap(active[neigh], active[node]);

        for (auto v : active[neigh])
            active[node].insert(v);
    }

    for (auto v : starting[node])
        active[node].insert(v);

    for (auto v : ending[node]) {
        active[node].erase(active[node].find(v));
        active[node].erase(active[node].find(v));
    }

    if (node)
        ans[edges[mp(node, ancestor[0][node])]] = active[node].size() ? *active[node].begin() : -1;
}

void calculate_ancestors(void)
{
    for (int up = 1; up < MAXLOG; up++) {
        ancestor[up].resize(N + 1);
        for (int i = 0; i <= N; i++)
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
    }
}

int main(void)
{
    freopen("disrupt.in", "r", stdin);
    freopen("disrupt.out", "w", stdout);

    scanf("%d %d", &N, &M);

    adj_list.resize(N);
    ancestor[0].resize(N + 1);
    active.resize(N);
    starting.resize(N);
    ending.resize(N);
    ans.resize(N - 1);
    dep.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);

        edges[mp(a, b)] = edges[mp(b, a)] = i;
    }

    dfs(0, 0);
    calculate_ancestors();

    for (int i = 0; i < M; i++) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        a--; b--;

        int L = lca(a, b);

        starting[a].pb(w);
        starting[b].pb(w);
        ending[L].pb(w);
    }

    getans(0);

    for (int i = 0; i < N - 1; i++)
        printf("%d\n", ans[i]);

    return 0;
}