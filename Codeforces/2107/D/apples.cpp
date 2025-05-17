#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

struct Path {
    int d;
    int u, v;
};

bool operator < (Path a, Path b) {
    return make_tuple(a.d, a.u, a.v) < make_tuple(b.d, b.u, b.v);
}

int N;
vector<vector<int>> adj_list;
vector<pi> opt;
vector<int> roots;

vector<int> p;
vector<Path> best;
vector<int> bestkid;

vector<bool> removed;

vector<set<Path>> ans;
set<Path> fin;

Path build(pi a, pi b) {
    int d = a.first + b.first - 1;
    int u = max(a.second, b.second);
    int v = min(a.second, b.second);

    return {d, u, v};
}

void dfs(int node, int par) {
    opt[node] = {1, node};
    best[node] = {1, node, node};
    bestkid[node] = node;
    p[node] = par;

    for (auto neigh : adj_list[node]) {
        if (neigh == par || removed[neigh]) {
            continue;
        }

        dfs(neigh, node);
        pi res = opt[neigh];
        res.first++;

        best[node] = max(best[node], build(opt[node], res));
        opt[node] = max(opt[node], res);

        if (best[bestkid[node]] < best[neigh]) {
            bestkid[node] = neigh;
        }
    }

    if (best[bestkid[node]] < best[node]) {
        bestkid[node] = node;
    }
}

void upwards(int node, int dest) {
    if (node == dest) {
        return;
    }

    for (auto neigh : adj_list[node]) {
        if (neigh != p[node] && !removed[neigh]) {
            roots.pb(neigh);
        }
    }

    removed[node] = true;
    upwards(p[node], dest);
}

void merge(set<Path>& a, set<Path>& b) {
    for (auto v : b) {
        a.insert(v);
    }
}

void calculate(int node, int par) {
    dfs(node, par);

    int split = bestkid[node];
    
    int u = best[split].u;
    int v = best[split].v;

    roots.clear();

    upwards(u, split);
    upwards(v, split);

    for (auto neigh : adj_list[split]) {
        if (!removed[neigh]) {
            roots.pb(neigh);
        }
    }
    removed[split] = true;
    
    ans[split].clear();
    ans[split].insert(best[split]);

    for (auto r : roots) {
        calculate(r, -1);

        if (ans[r].size() > ans[split].size()) {
            swap(ans[r], ans[split]);
        }
        merge(ans[split], ans[r]);
    }


    fin = ans[split];
}

void solve(void) {
    int N;
    scanf("%d", &N);

    adj_list.assign(N, vector<int>());
    ans.assign(N, set<Path>());
    removed.assign(N, false);
    best.resize(N);
    bestkid.resize(N);
    p.resize(N);
    roots.clear();
    opt.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    calculate(0, -2);

    for (auto it = fin.rbegin(); it != fin.rend(); it++) {
        Path p = *it;
        printf("%d %d %d ", p.d, p.u + 1, p.v + 1);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
}