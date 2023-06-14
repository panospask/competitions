#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct SegTree {

    int size;
    vector<ll> tree;
    int IDENTITY;
    ll (*f)(ll, ll);

    void init(int n, ll (*func)(ll, ll), int ID) {
        f = func;
        IDENTITY = ID;

        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = f(tree[2 * x + 1] , tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    ll get(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return IDENTITY;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ll g1 = get(l, r, 2 * x + 1, lx, mid);
        ll g2 = get(l, r, 2 * x + 2, mid, rx);

        return f(g1, g2);
    }
    ll get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

int n, q;
vector<int> val;
vector<int> par;
vector<int> depth;
vector<vector<pi>> adj_list;
SegTree distances;
SegTree euler;

vector<pi> edges;
vector<int> first;
vector<int> tin;
vector<int> tout;

int cnt1 = 0;
int cnt2 = 0;

ll find_earliest(ll a, ll b)
{
    if (a == n)
        return b;
    if (b == n)
        return a;

    if (depth[a] < depth[b])
        return a;
    else
        return b;
}
ll sum(ll a, ll b)
{
    return a + b;
}

void dfs(int node)
{
    tin[node] = cnt1++;
    distances.set(tin[node], val[node]);

    first[node] = cnt2;
    euler.set(cnt2++, node);

    for (auto kid : adj_list[node]) {
        if (kid.f != par[node]) {
            val[kid.f] = kid.s;
            depth[kid.f] = depth[node] + 1;
            par[kid.f] = node;

            dfs(kid.f);

            euler.set(cnt2++, node);
        }
    }

    tout[node] = cnt1++;
    distances.set(tout[node], -val[node]);
}

int lca(int a, int b)
{
    if (first[a] > first[b])
        swap(a, b);
    return euler.get(first[a], first[b] + 1);
}

// int man_lca(int a, int b)
// {
//     if (depth[a] < depth[b])
//         swap(a, b);

//     while (depth[a] > depth[b])
//         a = par[a];

//     while (a != b) {
//         a = par[a];
//         b = par[b];
//     }

//     return a;
// }

int main(void)
{
    scanf("%d", &n);

    tin.resize(n);
    tout.resize(n);
    first.resize(n);

    depth.resize(n + 1);
    depth[n] = INT_MAX;
    par.resize(n);
    val.resize(n);

    adj_list.resize(n);
    distances.init(2 * n, sum, 0);
    euler.init(2 * n - 1, find_earliest, n);

    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(mp(v, w));
        adj_list[v].pb(mp(u, w));

        edges.pb(mp(u, v));
    }

    // Arbitrary root;
    par[0] = -1;
    depth[0] = 0;
    val[0] = 0;
    dfs(0);

    scanf("%d", &q);
    while (q--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int u, v, w, i;
            scanf("%d %d", &i, &w);
            i--;

            tie(u, v) = edges[i];

            assert(u < n && v < n && u >= 0 && v >= 0);

            if (par[v] == u)
                swap(u, v);

            distances.set(tin[u], w);
            distances.set(tout[u], -w);
        }
        else {
            int u, v;
            scanf("%d %d", &u, &v);
            u--; v--;

            int l = lca(u, v);
            assert(l >= 0 && l <= n);
            // assert(l == man_lca(u, v));
            // ll d1 = distances.get(0, tin[u] + 1);
            // ll d2 = distances.get(0, tin[v] + 1);
            // ll d3 = distances.get(0, tin[l] + 1);
            ll ans = distances.get(0, tin[u] + 1) + distances.get(0, tin[v] + 1) - 2 * distances.get(0, tin[l] + 1);

            assert(ans >= 0);

            printf("%lld\n", ans);
        }
    }

    return 0;
}