#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct SegTree {
    int size;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, 0);
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            add(i, v, 2 * x + 1, lx, mid);
        }
        else {
            add(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        int s1 = calc(l, r, 2 * x + 1, lx, mid);
        int s2 = calc(l, r, 2 * x + 2, mid, rx);

        return s1 + s2;
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N, L, D;
SegTree st;
vector<vector<pi>> adj_list;

vector<int> dep;
vector<int> dist;
vector<int> subtree;
vector<bool> removed;

ll ans = 0;

// Given the node, the parent and the total number of nodes, finds the centroid
int find_centroid(int node, int par, int total)
{
    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par || removed[neigh]) {
            continue;
        }

        if (subtree[neigh] > total / 2) {
            return find_centroid(neigh, node, total);
        }
    }

    return node;
}

// Recalculate subtree of node as having parent par
void reroot(int node, int par)
{
    subtree[node] = 1;

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par || removed[neigh]) {
            continue;
        }

        dist[neigh] = dist[node] + w;
        dep[neigh] = dep[node] + 1;
        reroot(neigh, node);
        subtree[node] += subtree[neigh];
    }
}

void dfs(int node, int par, vector<pi>& k)
{
    k.push_back({dist[node], dep[node]});

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh != par && !removed[neigh]) {
            dfs(neigh, node, k);
        }
    }
}

vector<pi> compute(vector<pi>& a, vector<pi>& b)
{
    for (int i = 0; i < b.size(); i++) {
        st.add(b[i].second, 1);
    }
    int p = b.size() - 1;

    for (int i = 0; i < a.size(); i++) {
        while (p >= 0 && b[p].first + a[i].first > D) {
            st.add(b[p].second, -1);
            p--;
        }

        ans += st.calc(0, L - a[i].second + 1);
    }
    while (p >= 0) {
        st.add(b[p].second, -1);
        p--;
    }

    vector<pi> res(a.size() + b.size());
    p = 0;
    for (int i = 0; i < a.size(); i++) {
        while (p < b.size() && b[p].first < a[i].first) {
            res[i + p] = b[p];
            p++;
        }
        res[i + p] = a[i];
    }
    while (p < b.size()) {
        res[a.size() + p] = b[p];
        p++;
    }

    return res;
}

// Apply centroid decomposition in the subtree of node
void decompose(int node)
{
    int cen = find_centroid(node, -1, subtree[node]);

    dist[cen] = dep[cen] = 0;
    reroot(cen, -1);
    removed[cen] = true;

    vector<vector<pi>> kids;
    kids.push_back({{0, 0}});
    for (auto [neigh, w] : adj_list[cen]) {
        if (!removed[neigh]) {
            kids.push_back({});
            dfs(neigh, cen, kids.back());
            sort(kids.back().begin(), kids.back().end());
        }
    }

    vector<vector<pi>> nxt;
    while (kids.size() > 1) {
        for (int i = 1; i < kids.size(); i += 2) {
            nxt.push_back(compute(kids[i - 1], kids[i]));
        }

        if (kids.size() % 2) {
            nxt.push_back(kids.back());
        }

        swap(kids, nxt);
        nxt.clear();
    }

    for (auto [neigh, w] : adj_list[cen]) {
        if (!removed[neigh]) {
            decompose(neigh);
        }
    }
}

int main(void)
{
    scanf("%d %d %d", &N, &L, &D);

    adj_list.resize(N);
    removed.assign(N, false);
    subtree.resize(N);
    dep.resize(N);
    dist.resize(N);
    st.init(N);

    for (int i = 1; i < N; i++) {
        int p, w;
        scanf("%d %d", &p, &w);
        p--;

        adj_list[i].push_back({p, w});
        adj_list[p].push_back({i, w});
    }

    dep[0] = dist[0] = 0;
    reroot(0, -1);
    decompose(0);

    printf("%lld\n", ans);

    return 0;
}