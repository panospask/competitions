#include <bits/stdc++.h>
#define pb push_back
#define f first
#define s second
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct SegTree {

    int size;
    vector<ll> tree;
    vector<ll> lazy;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, 0);
        lazy.assign(2 * size, 0);
    }

    void propagate(int x, int lx, int rx) {
        int mid = (lx + rx) / 2;

        if (lazy[x] == 0)
            return;

        lazy[2 * x + 1] += lazy[x];
        tree[2 * x + 1] += (mid - lx) * lazy[x];

        lazy[2 * x + 2] += lazy[x];
        tree[2 * x + 2] += (rx - mid) * lazy[x];

        lazy[x] = 0;
    }

    void add(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            lazy[x] += v;
            tree[x] += (rx - lx) * (ll) v;
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, mid);
        add(l, r, v, 2 * x + 2, mid, rx);

        tree[x] += (min(r, rx) - max(l, lx)) * (ll) v;
    }
    void add(int l, int r, int v) {
        add(l, r, v, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;

        ll s1 = calc(l, r, 2 * x + 1, lx, mid);
        ll s2 = calc(l, r, 2 * x + 2, mid, rx);

        return s1 + s2;
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

SegTree values;

int N, Q;
const int C = 1e5 + 2;

vector<vector<int>> adj_list;

int counter = 0;
vector<int> tin;
vector<int> tout;

bool subtreecomp(int a, int b)
{
    return tin[a] < tin[b];
}
using cmp = integral_constant<decltype(&subtreecomp), &subtreecomp>;

vector<set<int, cmp>> colour_updates;

void dfs(int node, int par)
{
    tin[node] = counter++;

    for (auto neigh : adj_list[node])
        if (neigh != par)
            dfs(neigh, node);

    tout[node] = counter;
}

bool ancestor(int a, int b)
{
    return tin[a] < tin[b] && tout[a] >= tout[b];
}

int main(void)
{
    freopen("snowcow.in", "r", stdin);
    freopen("snowcow.out", "w", stdout);

    scanf("%d %d", &N, &Q);

    tin.resize(N);
    tout.resize(N);
    adj_list.resize(N);
    colour_updates.resize(C);
    values.init(N);

    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    dfs(0, -1);

    for (int i = 0; i < Q; i++) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int a, x;
            scanf("%d %d", &a, &x);
            a--;

            auto it = colour_updates[x].lower_bound(a);

            if (it != colour_updates[x].begin())
                it--;
            if (it != colour_updates[x].end() && ancestor(*it, a))
                continue;
            else {
                while (true) {
                    auto it = colour_updates[x].lower_bound(a);
                    if (it != colour_updates[x].end() && ancestor(a, *it)) {
                        int b = *it;
                        values.add(tin[b], tout[b], -1);
                        colour_updates[x].erase(it);
                    }
                    else {
                        break;
                    }
                }

                values.add(tin[a], tout[a], 1);
                colour_updates[x].insert(a);
            }
        }
        else {
            int a;
            scanf("%d", &a);
            a--;

            ll ans = values.calc(tin[a], tout[a]);
            printf("%lld\n", ans);
        }
    }

    return 0;
}