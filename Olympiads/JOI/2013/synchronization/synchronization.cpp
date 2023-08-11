#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

int N, M, Q;
vector<int> tin, par, sz, head, trav;
vector<int> par_edge;
vector<vector<pi>> adj_list;
vector<bool> available;
int counter = 0;

// Information if it is root and total info contained at removal time
vector<int> a, c;

// Set of roots at each heavy path
vector<set<int>> roots;

void decompose(int node, int h)
{
    head[node] = h;
    tin[node] = counter++;
    trav[tin[node]] = node;
    roots[h].insert(tin[node]);
    a[node] = 1;
    c[node] = 0;

    int BigKid = -1, BigV = 0;
    for (auto [neigh, w] : adj_list[node]) {
        if (neigh != par[node] && sz[neigh] > BigV) {
            BigV = sz[neigh];
            BigKid = neigh;
        }
    }

    if (BigKid != -1) {
        decompose(BigKid, h);
    }

    for (auto [neigh,  w] : adj_list[node]) {
        if (neigh != par[node] && neigh != BigKid)
            decompose(neigh, neigh);
    }
}

void init(int node)
{
    sz[node] = 1;

    for (auto [neigh, id] : adj_list[node]) {
        if (neigh != par[node]) {
            par[neigh] = node;
            init(neigh);
            sz[node] += sz[neigh];
        }
        else {
            par_edge[id] = node;
        }
    }
}

int find_root(int v)
{
    while (roots[head[v]].upper_bound(tin[v]) == roots[head[v]].begin())
        v = par[head[v]];

    auto it = roots[head[v]].upper_bound(tin[v]);
    it--;

    return trav[*it];
}

// Insert edge between u and parent
void insert_edge(int u)
{
    int r = find_root(par[u]);

    a[r] = a[r] + a[u] - c[u];
    roots[head[u]].erase(tin[u]);
}

// Remove edge between u and parent
void remove_edge(int u)
{
    int r = find_root(u);
    c[u] = a[r];
    a[u] = a[r];

    roots[head[u]].insert(tin[u]);
}

int main(void)
{
    scanf("%d %d %d", &N, &M, &Q);

    adj_list.resize(N);
    roots.resize(N);
    head.resize(N);
    par_edge.resize(N);
    sz.resize(N);
    par.resize(N);
    tin.resize(N);
    trav.resize(N);
    a.resize(N);
    c.resize(N);
    available.assign(N - 1, false);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(mp(v, i));
        adj_list[v].pb(mp(u, i));
    }

    par[0] = -1;
    init(0);
    decompose(0, 0);

    while (M--) {
        int t;
        scanf("%d", &t);
        t--;

        int u = par_edge[t];
        if (available[t]) {
            remove_edge(u);
        }
        else {
            insert_edge(u);
        }

        available[t] = !available[t];
    }

    while (Q--) {
        int v;
        scanf("%d", &v);
        v--;

        int r = find_root(v);
        printf("%d\n", a[r]);
    }
}