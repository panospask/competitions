#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

const int MOD = 998244353;

typedef pair<int, int> pi;
typedef long long ll;

// Range nullify, point add
struct SegTree {
    int size;
    vector<bool> op;
    vector<ll> tree;
    bool mul;

    int neutral(void) {
        return mul;
    }

    ll merge(ll a, ll b) {
        if (mul)
            return a * b % MOD;
        else
            return (a + b) % MOD;
    }

    void init(int n, bool m) {
        size = 1;
        mul = m;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, neutral());
        op.assign(2 * size, false);
    }

    void propagate(int x) {
        if (!op[x])
            return;

        tree[2 * x + 1] = tree[2 * x + 2] = neutral();
        op[2 * x + 1] = op[2 * x + 2] = true;

        op[x] = false;
    }

    void null(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x] = neutral();
            op[x] = true;

            return;
        }

        propagate(x);
        int mid = (lx + rx) / 2;

        null(l, r, 2 * x + 1, lx, mid);
        null(l, r, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void null(int l, int r) {
        null(l, r, 0, 0, size);
    }

    void add(int i, ll v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = merge(tree[x], v);
            return;
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        if (i < mid)
            add(i, v, 2 * x + 1, lx, mid);
        else
            add(i, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int i, ll v) {
        add(i, v, 0, 0, size);
    }

    ll get(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return neutral();
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        return merge(get(l, r, 2 * x + 1, lx, mid), get(l, r, 2 * x + 2, mid, rx));
    }
    ll get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

int N, S;

int TotalVals;

SegTree cnt, vals;
vector<int> weights;
vector<int> sz;
vector<vector<pi>> adj_list;

vector<int> maxs;

ll ans = 1;

ll calcpow(ll a, int b)
{
    ll c = 1;

    while (b) {
        if (b % 2)
            c = c * a % MOD;

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

int find(int w)
{
    return lower_bound(weights.begin(), weights.end(), w) - weights.begin();
}

void calcmax(int node, int par, int m)
{
    maxs.pb(m);

    for (auto [neigh, w] : adj_list[node])
        if (neigh != par)
            calcmax(neigh, node, max(m, w));
}

void calcsz(int node, int par)
{
    sz[node] = 1;

    for (auto [neigh, w] : adj_list[node])
        if (neigh != par) {
            calcsz(neigh, node);
            sz[node] += sz[neigh];
        }
}

void dfs(int node, int par, bool keep)
{
    int BigKid = -1;
    int BigV = 0;
    int BigW = 0;

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par )
            continue;

        if (sz[neigh] > BigV) {
            BigV = sz[neigh];
            BigKid = neigh;
            BigW = w;
        }
    }

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par || neigh == BigKid)
            continue;

        dfs(neigh, node, false);
    }
    if (BigKid == -1)
        return;

    dfs(BigKid, node, true);

    // Set all values to at least BigW
    int pos = find(BigW);

    int tot_smaller = cnt.get(0, pos);

    cnt.null(0, pos);
    vals.null(0, pos);

    cnt.add(pos, tot_smaller);
    vals.add(pos, calcpow(S - BigW, tot_smaller));

    ans = (ans * vals.get(0, TotalVals)) % MOD;

    // Also add an extra w for BigKid
    cnt.add(pos, 1);
    vals.add(pos, S - BigW);

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par || neigh == BigKid)
            continue;

        maxs.clear();
        calcmax(neigh, node, w);

        for (int i = 0; i < maxs.size(); i++) {
            if (i) {
                // Also merge with current node
                ans = (ans * (S - maxs[i])) % MOD;
            }

            int p = find(maxs[i]);

            int bef = cnt.get(0, p);
            ll aft = vals.get(p, TotalVals);

            ll mul = (calcpow(S - maxs[i], bef) * aft) % MOD;
            ans = (ans * mul) % MOD;
        }
        for (int i = 0; i < maxs.size(); i++) {
            int p = find(maxs[i]);

            cnt.add(p, 1);
            vals.add(p, S - maxs[i]);
        }

        maxs.clear();
    }

    if (!keep) {
        cnt.null(0, TotalVals);
        vals.null(0, TotalVals);
    }
}

int solve(void)
{
    adj_list.clear();
    sz.clear();
    weights.clear();
    ans = 1;

    scanf("%d %d", &N, &S);
    S++;

    adj_list.resize(N);
    sz.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        weights.pb(w);

        adj_list[u].pb(mp(v, w));
        adj_list[v].pb(mp(u, w));
    }

    sort(weights.begin(), weights.end());
    weights.resize(unique(weights.begin(), weights.end()) - weights.begin());

    TotalVals = weights.size();

    vals.init(TotalVals, true);
    cnt.init(TotalVals, false);

    calcsz(0, -1);
    dfs(0, -1, false);

    ans %= MOD;
    printf("%lld\n", ans);

    return 0;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}