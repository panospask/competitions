#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct SegTree {

    int size;
    vector<ll> tree;

    void init(int n) {
        size = 1;
        while (size < n) {
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
        if (i < mid)
            add(i, v, 2 * x + 1, lx, mid);
        else
            add(i, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    ll sum(int l, int r, int x, int lx ,int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ll s1 = sum(l, r, 2 * x + 1, lx, mid);
        ll s2 = sum(l, r, 2 * x + 2, mid, rx);

        return s1 + s2;
    }
    ll sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};

const int C = 1e5;

int N, Q;
vector<vector<pi>> queries;
vector<vector<pi>> colourings;

vector<vector<int>> adj_list;
vector<ll> ans;
vector<int> earliest;

SegTree values;

void init_values(void)
{
    queries.resize(N);
    colourings.resize(N);

    adj_list.resize(N);
    ans.assign(Q, -1);
    values.init(Q + 1);
    earliest.assign(C + 1, Q);
}

void dfs(int node, int par)
{
    // Add the colourings that happened in this node
    vector<pi> added;
    vector<pi> rmed;
    for (auto event : colourings[node]) {
        int t = earliest[event.s];
        if (event.f < t) {
            values.add(event.f, event.s);
            values.add(t, -event.s);

            added.pb(mp(event.f, event.s));
            rmed.pb(mp(t, event.s));
        }
    }

    // Process queries
    for (auto q : queries[node]) {
        ans[q.s] = values.sum(0, q.f);
    }

    // And children
    for (auto& neigh : adj_list[node]) {
        if (neigh != par)
            dfs(neigh, node);
    }

    // Remove colourings
    for (auto v : added) {
        values.add(v.f, -v.s);
    }
    for (auto v : rmed) {
        values.add(v.f, v.s);
    }
}

int main(void)
{
    freopen("snowcow.in", "r", stdin);
    freopen("snowcow.out", "w", stdout);

    scanf("%d %d", &N, &Q);

    init_values();

    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }
    for (int i = 0; i < Q; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int a, col;
            scanf("%d %d", &a, &col);
            a--;

            colourings[a].push_back(mp(i, col));
        }
        else {
            int a;
            scanf("%d", &a);
            a--;

            queries[a].push_back(mp(i, i));
        }
    }
    for (int i = 0; i < N; i++)
        sort(colourings[i].begin(), colourings[i].end());

    dfs(0, -1);

    for (int i = 0; i < Q; i++)
        if (ans[i] != -1)
            printf("%lld\n", ans[i]);

    return 0;
}