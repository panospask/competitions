#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct LazySegTree {

    int size;
    ll IDENTITY = 1e12;
    vector<ll> tree;
    vector<ll> lazy;

    void init(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }

        tree.assign(2 * size, 0);
        lazy.assign(2 * size, false);
    }

    void propagate(int x, int lx, int rx) {
        int mid = (lx + rx) / 2;

        if (lazy[x] == 0)
            return;

        lazy[2 * x + 1] += lazy[x];
        tree[2 * x + 1] += lazy[x];

        lazy[2 * x + 2] += lazy[x];
        tree[2 * x + 2] += lazy[x];

        lazy[x] = 0;
    }

    void add(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x] += v;
            lazy[x] += v;
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;

        add(l, r, v, 2 * x + 1, lx, mid);
        add(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int l, int r, int v) {
        add(l, r, v, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return IDENTITY;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;

        ll c1 = calc(l, r, 2 * x + 1, lx, mid);
        ll c2 = calc(l, r, 2 * x + 2, mid, rx);

        return min(c1, c2);
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

struct SumTree {
    int size;
    vector<ll> tree;

    void init(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }

        tree.assign(2 * size, false);
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            add(i, v, 2 * x + 1, lx, mid);
        else
            add(i, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;

        ll c1 = calc(l, r, 2 * x + 1, lx, mid);
        ll c2 = calc(l, r, 2 * x + 2, mid, rx);

        return c1 + c2;
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

struct Edge {
    int a, b, w, id;
};

int n, q;
vector<vector<int>> kids;
vector<int> to_par;
vector<Edge> edges;
vector<int> to_root;
LazySegTree root_up;
SumTree root_down;

int counter = 0;
vector<int> tin;
vector<int> tout;

bool ancestor(int a, int b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

void dfs(int node)
{
    tin[node] = counter++;

    for (auto kid : kids[node])
        dfs(kid);

    tout[node] = counter;

    root_down.add(tin[node], to_par[node]);
    root_down.add(tout[node], -to_par[node]);

    root_up.add(tin[node], tout[node], to_par[node]);
    root_up.add(tin[node], tin[node] + 1, to_root[node]);
}

int main(void)
{
    scanf("%d %d", &n, &q);

    kids.resize(n);
    to_par.resize(n);
    to_root.resize(n);
    tin.resize(n);

    root_down.init(n);
    root_up.init(n);

    tout.resize(n);
    edges.resize(2 * n - 2);

    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        a--; b--;

        edges[i] = {a, b, w, i};
        kids[a].push_back(b);
        to_par[b] = w;
    }
    for (int i = n - 1; i < 2 * (n - 1); i++) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        a--; b--;

        edges[i] = {a, b, w, i};
        to_root[a] = w;
    }
    to_par[0] = 0;

    dfs(0);

    while (q--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int i, w;
            scanf("%d %d", &i, &w);
            i--;

            if (i < n - 1) {
                int b = edges[i].b;

                int diff = w - to_par[b];

                root_up.add(tin[b], tout[b], diff);
                root_down.add(tin[b], diff);
                root_down.add(tout[b], -diff);

                to_par[b] = w;
            }
            else {
                int a = edges[i].a;
                root_up.add(tin[a], tin[a] + 1, -to_root[a]);
                to_root[a] = w;
                root_up.add(tin[a], tin[a] + 1, to_root[a]);
            }
        }
        else {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;

            ll ans = 0;

            if (ancestor(a, b)) {
                ans = root_down.calc(0, tin[b] + 1) - root_down.calc(0, tin[a] + 1);
            }
            else {
                ll up = root_up.calc(tin[a], tout[a]) - root_down.calc(0, tin[a] + 1);
                ll dn = root_down.calc(0, tin[b] + 1);

                ans = up + dn;
            }
            printf("%lld\n", ans);
        }
    }

    return 0;
}