#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

struct SegTree {
    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
    }

    void add(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, mid);
        add(l, r, v, 2 * x + 2, mid, rx);
    }
    void add(int l, int r, int v) {
        add(l, r, v, 0, 0, size);
    }

    int get(int i, int x, int lx, int rx) {
        if (lx == rx - 1) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        int r;
        if (i < mid)
            r = get(i, 2 * x + 1, lx, mid);
        else
            r = get(i, 2 * x + 2, mid, rx);

        return r + tree[x];
    }
    int get(int i) {
        return get(i, 0, 0, size);
    }
};

int N, M;
SegTree st;

vector<int> head;
vector<int> par;
vector<int> id;
vector<int> sz;
vector<int> dep;
vector<vector<int>> adj_list;
int counter = 0;

void decompose(int node, int h)
{
    head[node] = h;
    id[node] = counter++;

    int BigKid = -1, BigV = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh == par[node])
            continue;

        if (sz[neigh] > BigV) {
            BigKid = neigh;
            BigV = sz[neigh];
        }
    }

    if (BigKid != -1)
        decompose(BigKid, h);

    for (auto neigh : adj_list[node]) {
        if (neigh != par[node] && neigh != BigKid)
            decompose(neigh, neigh);
    }
}

void Update(int u, int v)
{
    while (head[u] != head[v]) {
        if (dep[head[u]] < dep[head[v]])
            swap(u, v);

        st.add(id[head[u]], id[u] + 1, 1);
        u = par[head[u]];
    }

    if (dep[u] < dep[v])
        swap(u, v);

    st.add(id[v] + 1, id[u] + 1, 1);
}

void init(int node)
{
    sz[node] = 1;
    for (auto neigh : adj_list[node])
        if (neigh != par[node]) {
            par[neigh] = node;
            dep[neigh] = dep[node] + 1;
            init(neigh);
            sz[node] += sz[neigh];
        }
}

int GetAnswer(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);

    return st.get(id[u]);
}

int main(void)
{
    scanf("%d %d", &N, &M);

    adj_list.resize(N);
    st.init(N);
    id.resize(N);
    sz.resize(N);
    head.resize(N);
    dep.resize(N);
    par.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    dep[0] = 0;
    par[0] = -1;
    init(0);
    decompose(0, 0);

    while (M--) {
        char op;
        int u, v;
        scanf(" %c %d %d", &op, &u, &v);
        u--; v--;

        if (op == 'P') {
            Update(u, v);
        }
        else {
            printf("%d\n", GetAnswer(u, v));
        }
    }

    return 0;
}