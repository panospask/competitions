#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int INF = 1e9;
const int MAXUP = 19;

int N, K;
vector<vector<int>> adj_list;
vector<int> f, p;
vector<bool> is_shop;
vector<vector<int>> ancestor;

vector<int> maxdist;
vector<int> closest;

// Centroid decomposition variables
vector<int> dep;
vector<int> subtree;
vector<bool> removed;

vector<int> ans;

void dfs(int node, int par)
{
    subtree[node] = 1;

    for (auto neigh : adj_list[node]) {
        if (neigh == par || removed[neigh]) {
            continue;
        }

        dep[neigh] = dep[node] + 1;
        dfs(neigh, node);
        subtree[node] += subtree[neigh];
    }
}

int find_centroid(int node, int par, int total)
{
    for (auto neigh : adj_list[node]) {
        if (neigh == par || removed[neigh]) {
            continue;
        }

        if (subtree[neigh] > total / 2) {
            return find_centroid(neigh, node, total);
        }
    }

    return node;
}

void insert(int node, int par, vector<int>& l)
{
    l.pb(node);

    for (auto neigh : adj_list[node]) {
        if (neigh != par && !removed[neigh]) {
            insert(neigh, node, l);
        }
    }
}

bool customsort(int a, int b)
{
    return maxdist[a] - dep[a] > maxdist[b] - dep[b];
}

bool depsort(int a, int b)
{
    return dep[a] < dep[b];
}

bool valid(int u, int v)
{
    return dep[u] <= maxdist[v] - dep[v];
}

vector<int> process(vector<int>& a, vector<int>& b)
{
    sort(a.begin(), a.end(), depsort);
    sort(b.begin(), b.end(), customsort);

    int p = b.size() - 1;
    for (int i = 0; i < a.size(); i++) {
        while (p >= 0 && !valid(a[i], b[p])) {
            p--;
        }

        ans[a[i]] += p + 1;
    }

    sort(b.begin(), b.end(), depsort);
    sort(a.begin(), a.end(), customsort);

    p = a.size() - 1;
    for (int i = 0; i < b.size(); i++) {
        while (p >= 0 && !valid(b[i], a[p])) {
            p--;
        }

        ans[b[i]] += p + 1;
    }

    vector<int> res(a.size() + b.size());
    for (int i = 0; i < a.size(); i++) {
        res[i] = a[i];
    }
    for (int i = 0; i < b.size(); i++) {
        res[i + a.size()] = b[i];
    }

    return res;
}

void decompose(int node)
{
    node = find_centroid(node, -1, subtree[node]);

    dep[node] = 0;
    dfs(node, -1);

    removed[node] = true;

    vector<vector<int>> kids;
    kids.pb({node});
    for (auto neigh : adj_list[node]) {
        if (!removed[neigh]) {
            kids.push_back({});
            insert(neigh, node, kids.back());
        }
    }

    vector<vector<int>> nxt;
    while (kids.size() > 1) {
        for (int i = 1; i < kids.size(); i += 2) {
            nxt.pb(process(kids[i - 1], kids[i]));
        }
        if (kids.size() % 2) {
            nxt.pb(kids.back());
        }

        swap(kids, nxt);
        nxt.clear();
    }
    kids.clear();

    for (auto neigh : adj_list[node]) {
        if (!removed[neigh]) {
            decompose(neigh);
        }
    }
}

void initialize(int node, int par)
{
    if (is_shop[node]) {
        closest[node] = 0;
    }
    ancestor[0][node] = par;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dep[neigh] = dep[node] + 1;
        initialize(neigh, node);
        closest[node] = min(closest[node], closest[neigh] + 1);
    }
}

void reroot(int node, int par)
{
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }
        closest[neigh] = min(closest[neigh], closest[node] + 1);
        reroot(neigh, node);
    }
}

int jump(int a, int v)
{
    for (int up = 0; up < MAXUP; up++) {
        if (v & (1 << up)) {
            a = ancestor[up][a];
        }
    }

    return a;
}

int lca(int a, int b)
{
    if (dep[a] < dep[b]) {
        swap(a, b);
    }

    a = jump(a, dep[a] - dep[b]);
    if (a == b) {
        return a;
    }

    for (int up = MAXUP - 1; up >= 0; up--) {
        int n_a = ancestor[up][a];
        int n_b = ancestor[up][b];

        if (n_a != n_b) {
            a = n_a;
            b = n_b;
        }
    }

    return ancestor[0][a];
}

void precalculate(void)
{
    for (int up = 1; up < MAXUP; up++) {
        for (int i = 0; i < N; i++) {
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
        }
    }
}

int dist(int u, int v)
{
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

int main(void)
{
    scanf("%d %d", &N, &K);

    adj_list.resize(N);
    dep.resize(N);
    f.resize(N);
    p.resize(N);
    is_shop.assign(N, false);
    subtree.resize(N);
    removed.assign(N, false);
    closest.assign(N, INF);
    ancestor.resize(MAXUP, vector<int>(N));
    maxdist.resize(N);
    ans.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }
    for (int i = 0; i < K; i++) {
        int u;
        scanf("%d", &u);
        u--;

        is_shop[u] = true;
    }
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &f[i], &p[i]);
        f[i]--;
    }

    initialize(0, 0);
    reroot(0, 0);
    precalculate();

    for (int i = 0; i < N; i++) {
        maxdist[i] = min(closest[i], dist(i, f[i]) - p[i] - 1);

        if (maxdist[i] >= 0) {
            ans[i]++;
        }
    }

    dfs(0, 0);
    decompose(0);

    for (int i = 0; i < N; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");

    return 0;
}