#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

const int INF = 1e6;

struct Node {
    int total;
    int max;
};
const Node NEUTRAL = {0, -INF};

// Best path starting from the latest node of b
Node merge(Node a, Node b)
{
    return {a.total + b.total, max(b.max, a.max + b.total)};
}

struct Segtree {
    const int NO_OP = -INF;

    int size;
    vector<Node> tree;
    vector<int> op;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
        op.assign(2 * size, 0);
    }

    void propagate(int x, int lx, int rx) {
        if (op[x] == NO_OP) {
            return;
        }

        int mid = (lx + rx) / 2;
        op[2 * x + 1] = op[x];
        tree[2 * x + 1].total = op[x] * (mid - lx);
        tree[2 * x + 1].max = max(tree[2 * x + 1].total, op[x]);
        op[2 * x + 2] = op[x];
        tree[2 * x + 2].total = op[x] * (rx - mid);
        tree[2 * x + 2].max = max(tree[2 * x + 2].total, op[x]);

        op[x] = NO_OP;
    }

    void set(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x].total = (rx - lx) * v;
            tree[x].max = max(tree[x].total, v);
            op[x] = v;
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        set(l, r, v, 2 * x + 1, lx, mid);
        set(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
        return;
    }
    void set(int l, int r, int v) {
        set(l, r, v, 0, 0, size);
    }

    Node calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        Node c1 = calc(l, r, 2 * x + 1, lx, mid);
        Node c2 = calc(l, r, 2 * x + 2, mid, rx);

        return merge(c1, c2);
    }
    Node calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N, Q;
Segtree st;
int counter = 0;
vector<int> tin;
vector<int> tout;
vector<int> par, head, sz;
vector<vector<int>> adj_list;

// Best suffix sum in path u -> root
int find_best(int u)
{
    Node cur = NEUTRAL;
    while (u != -1) {
        cur = merge(st.calc(tin[head[u]], tin[u] + 1), cur);
        u = par[head[u]];
    }

    return cur.max;
}

void make_white(int v)
{
    st.set(tin[v], tout[v], -1);

    int mod = find_best(v);
    if (mod >= 0) {
        // Modify value of v s.t the best path would add up to -1
        int cur = st.calc(tin[v], tin[v] + 1).total;
        st.set(tin[v], tin[v] + 1, cur - mod - 1);
    }
}

void make_black(int v)
{
    int cur = st.calc(tin[v], tin[v] + 1).total;
    st.set(tin[v], tin[v] + 1, cur + 1);
}

void decompose(int node, int h)
{
    tin[node] = counter++;
    st.set(tin[node], tin[node] + 1, -1);

    head[node] = h;
    int BigKid = -1, BigV = 0;

    for (auto neigh : adj_list[node]) {
        if (neigh != par[node] && sz[neigh] > BigV) {
            BigKid = neigh;
            BigV = sz[neigh];
        }
    }

    if (BigKid + 1)
        decompose(BigKid, h);

    for (auto neigh : adj_list[node]) {
        if (neigh != BigKid && neigh != par[node])
            decompose(neigh, neigh);
    }

    tout[node] = counter;
}

void init(int node)
{
    sz[node] = 1;

    for (auto neigh : adj_list[node]) {
        if (neigh == par[node])
            continue;

        par[neigh] = node;
        init(neigh);
        sz[node] += sz[neigh];
    }
}

int main(void)
{
    scanf("%d %d", &N, &Q);

    st.init(N);
    adj_list.resize(N);
    tin.resize(N);
    tout.resize(N);
    sz.resize(N);
    par.resize(N);
    head.reserve(N);

    for (int i = 1; i < N; i++) {
        int u;
        scanf("%d", &u);
        u--;

        adj_list[u].pb(i);
        adj_list[i].pb(u);
    }

    par[0] = -1;
    init(0);
    decompose(0, 0);

    while (Q--) {
        int op, v;
        scanf("%d %d", &op, &v);
        v--;

        if (op == 1) {
            make_black(v);
        }
        else if (op == 2) {
            make_white(v);
        }
        else {
            int res = find_best(v);
            if (res >= 0)
                printf("black\n");
            else
                printf("white\n");
        }
    }

    return 0;
}