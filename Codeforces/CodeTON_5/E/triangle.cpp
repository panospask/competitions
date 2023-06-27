#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const ll INF = 1e15;

struct SegTree {

    int size;
    vector<ll> tree;
    vector<ll> lazy;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, -INF);
        lazy.resize(2 * size);
    }

    void prop(int x) {
        if (lazy[x] == 0)
            return;

        lazy[2 * x + 1] += lazy[x];
        lazy[2 * x + 2] += lazy[x];

        tree[2 * x + 1] += lazy[x];
        tree[2 * x + 2] += lazy[x];

        lazy[x] = 0;
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            lazy[x] = 0;
            return;
        }

        prop(x);

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    void add(int l, int r, ll v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            lazy[x] += v;
            tree[x] += v;
            return;
        }

        prop(x);

        int mid = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, mid);
        add(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int l, int r, ll v) {
        add(l, r, v, 0, 0, size);
    }

    ll get(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return -INF;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        prop(x);

        int mid = (lx + rx) / 2;
        ll g1 = get(l, r, 2 * x + 1, lx, mid);
        ll g2 = get(l, r, 2 * x + 2, mid, rx);

        return max(g1, g2);
    }
    ll get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

int n, k, A;
ll total_cost = 0;

vector<vector<pi>> by_x_coord;

// dp[i] : Maximum saving potential when considering
// all the points in the triangle formed by the x axis and (k-i,i)
vector<ll> dp;

SegTree opt_triangle;

int main(void)
{
    scanf("%d %d %d", &n, &k, &A);

    by_x_coord.resize(k + 1);

    for (int i = 0; i < n; i++) {
        int x, y, c;
        scanf("%d %d %d", &x, &y, &c);

        total_cost += c;

        by_x_coord[x].pb(mp(y, c));
    }

    opt_triangle.init(k + 1);
    dp.resize(k + 1);


    dp[0] = 0;
    opt_triangle.set(0, 0);
    for (int y = 1; y <= k; y++) {
        dp[y] = dp[y - 1];

        // Update the triangles
        opt_triangle.add(0, y, -A);

        for (auto p : by_x_coord[k - y]) {
            opt_triangle.add(0, p.f + 1, p.s);
        }

        dp[y] = max(dp[y], opt_triangle.get(0, y));

        opt_triangle.set(y, dp[y]);
    }

    printf("%lld\n", total_cost - dp[k]);

    return 0;
}