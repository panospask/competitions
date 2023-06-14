#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;

struct SegTree {

    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, 0);
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

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int sum(int l, int r, int x, int lx ,int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        return sum(l, r, 2 * x + 1, lx, mid) + sum(l, r, 2 * x + 2, mid, rx);
    }
    int sum(int l, int r) {
        return sum(l, r, 0 ,0, size);
    }
};

int n;
vector<int> col;
map<int, int> latest_used;
vector<vector<int>> adj_list;
vector<int> ans;
vector<pair<pi, int>> queries;
SegTree vals;

vector<int> tin;
vector<int> tout;
vector<int> euler;
int counter = 0;

void dfs(int node, int par)
{
    tin[node] = counter++;
    euler.push_back(col[node]);

    for (auto neigh : adj_list[node])
        if (neigh != par)
            dfs(neigh, node);

    tout[node] = counter;
}

int main(void)
{
    scanf("%d", &n);

    col.resize(n);
    tin.resize(n);
    tout.resize(n);
    adj_list.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &col[i]);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    dfs(0, -1);

    queries.resize(n);
    ans.resize(n);
    for (int i = 0; i < n; i++) {
        queries[i] = mp(mp(tin[i], tout[i]), i);
    }

    sort(queries.rbegin(), queries.rend());

    int curp = 0;
    vals.init(n);
    for (int i = n - 1; i >= 0; i--) {
        int colour = euler[i];

        vals.set(latest_used[colour], 0);
        vals.set(i, 1);
        latest_used[colour] = i;

        while (curp < n && queries[curp].f.f == i) {
            auto cur = queries[curp];
            ans[cur.s] = vals.sum(cur.f.f, cur.f.s);

            curp++;
        }
    }

    for (int i = 0; i < n; i++)
        printf("%d ", ans[i]);
    printf("\n");

    return 0;
}