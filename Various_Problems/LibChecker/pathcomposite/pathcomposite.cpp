#include <bits/stdc++.h>
#define mp make_pair
#define f first
#define pb push_back
#define s second

using namespace std;

const int MOD = 998244353;

typedef long long ll;
typedef pair<ll, ll> pi;

// Returns f2(f1(x))
pi merge(pi a, pi b, bool inv) {
    if (inv)
        swap(a, b);

    pi c;
    c.f = a.f * b.f % MOD;
    c.s = (a.s * b.f + b.s) % MOD;

    return c;
}

struct SegTree {
    int size;
    vector<pi> tree;
    bool inv;

    const pi NEUTRAL = mp(1, 0);

    void init(int n, bool a) {
        inv = a;

        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, NEUTRAL);
    }

    void set(int i, pi v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2], inv);
    }
    void set(int i, pi v) {
        set(i, v, 0, 0, size);
    }

    pi calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        pi a = calc(l, r, 2 * x + 1, lx, mid);
        pi b = calc(l, r, 2 * x + 2, mid, rx);

        return merge(a, b, inv);
    }
    pi calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N, Q;
int counter = 0;
SegTree s1, s2;
vector<pi> v;
vector<int> head, par, dep, sz, id;
vector<vector<int>> adj_list;

// Query u -> v
pi query(int u, int v)
{
    pi r1 = {1, 0}, r2 = {1, 0};
    while (head[u] != head[v]) {
        if (dep[head[u]] > dep[head[v]]) {
            r1 = merge(r1, s1.calc(id[head[u]], id[u] + 1), false);
            u = par[head[u]];
        }
        else {
            r2 = merge(r2, s2.calc(id[head[v]], id[v] + 1), true);
            v = par[head[v]];
        }
    }

    if (dep[u] > dep[v]) {
        r1 = merge(r1, s1.calc(id[v], id[u] + 1), false);
    }
    else {
        r2 = merge(r2, s2.calc(id[u], id[v] + 1), true);
    }

    return merge(r1, r2, false);
}

void update(int i, pi v)
{
    s1.set(id[i], v);
    s2.set(id[i], v);
}

void decompose(int node, int h)
{
    head[node] = h;
    id[node] = counter++;

    s1.set(id[node], v[node]);
    s2.set(id[node], v[node]);

    int h_c = -1, h_v = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh == par[node])
            continue;

        if (h_v < sz[neigh]) {
            h_v = sz[neigh];
            h_c = neigh;
        }
    }

    if (h_c != -1)
        decompose(h_c, h);

    for (auto neigh : adj_list[node]) {
        if (neigh != par[node] && neigh != h_c)
            decompose(neigh, neigh);
    }
}

void init(int node)
{
    sz[node] = 1;

    for (auto neigh : adj_list[node]) {
        if (neigh != par[node]) {
            par[neigh] = node;
            dep[neigh] = dep[node] + 1;
            init(neigh);

            sz[node] += sz[neigh];
        }
    }
}

int main(void)
{
    scanf("%d %d", &N, &Q);

    s1.init(N, true);
    s2.init(N, false);

    id.resize(N);
    dep.resize(N);
    sz.reserve(N);
    par.resize(N);
    head.resize(N);
    v.resize(N);
    adj_list.resize(N);

    for (int i = 0; i < N; i++)
        scanf("%lld %lld", &v[i].f, &v[i].s);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    dep[0] = 0;
    par[0] = -1;
    init(0);
    decompose(0, 0);

    while (Q--) {
        int op;
        scanf("%d", &op);

        if (op == 0) {
            int p, c, d;
            scanf("%d %d %d", &p, &c, &d);

            update(p, mp(c, d));
        }
        else {
            int u, v, x;
            scanf("%d %d %d", &u, &v, &x);

            pi res = query(u, v);
            ll ans = (res.f * x + res.s) % MOD;

            printf("%lld\n", ans);
        }
    }

    return 0;
}