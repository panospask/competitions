#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int INF = 1e7;

int N;
int leafs;
vector<vector<int>> adj_list;
vector<int> leafdist;
vector<int> modify;

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
        if (neigh == par || removed[neigh]) {
            continue;
        }

        insert(neigh, node, l);
    }
}

bool depsort(int a, int b)
{
    return dep[a] > dep[b];
}

bool leafsort(int a, int b)
{
    return leafdist[a] - dep[a] < leafdist[b] - dep[b];
}

bool valid(int u, int v)
{
    return dep[u] >= leafdist[v] - dep[v];
}

vector<int> process(vector<int>& a, vector<int>& b)
{
    sort(a.begin(), a.end(), depsort);
    sort(b.begin(), b.end(), leafsort);

    vector<int> pref(b.size() + 1);
    pref[0] = 0;
    for (int i = 0; i < b.size(); i++) {
        pref[i + 1] = pref[i] + modify[b[i]];
    }

    int p = b.size() - 1;
    for (int i = 0; i < a.size(); i++) {
        while (p >= 0 && !valid(a[i], b[p])) {
            p--;
        }

        ans[a[i]] += pref[p + 1];
    }

    sort(a.begin(), a.end(), leafsort);
    sort(b.begin(), b.end(), depsort);

    pref.resize(a.size() + 1);
    pref[0] = 0;
    for (int i = 0; i < a.size(); i++) {
        pref[i + 1] = pref[i] + modify[a[i]];
    }

    p = a.size() - 1;
    for (int i = 0; i < b.size(); i++) {
        while (p >= 0 && !valid(b[i], a[p])) {
            p--;
        }

        ans[b[i]] += pref[p + 1];
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
            kids.pb({});
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

    for (auto neigh : adj_list[node]) {
        if (!removed[neigh]) {
            decompose(neigh);
        }
    }
}

void precalculate(void)
{
    leafdist.assign(N, INF);

    queue<int> q;
    for (int i = 0; i < N; i++) {
        modify[i] = -(adj_list[i].size() - 2);
        if (adj_list[i].size() == 1) {
            leafdist[i] = 0;
            q.push(i);
            leafs++;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto v : adj_list[u]) {
            if (leafdist[v] == INF) {
                leafdist[v] = leafdist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main(void)
{
    freopen("atlarge.in", "r", stdin);
    freopen("atlarge.out", "w", stdout);

    scanf("%d", &N);

    adj_list.resize(N);
    leafdist.resize(N);
    modify.resize(N);
    dep.resize(N);
    subtree.resize(N);
    removed.assign(N, false);
    ans.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }
    precalculate();

    dfs(0, -1);
    decompose(0);

    for (int i = 0; i < N; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}