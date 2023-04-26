#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

struct segtree {

    int size = 1;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(size * 2);
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

    int sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        auto s1 = sum(l, r, 2 * x + 1, lx, mid);
        auto s2 = sum(l, r, 2 * x + 2, mid, rx);

        return s1 + s2;
    }
    int sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};

int n;
vector<vector<int>> adj_list;
vector<ii> p;
vector<int> tin;
vector<int> tout;
vector<int> ans;
segtree st;
int counter = 0;

void dfs(int node, int par)
{
    tin[node] = counter++;

    for (auto neigh: adj_list[node])
        if (neigh != par)
            dfs(neigh, node);

    tout[node] = counter;
    return;
}

int main(void)
{
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);

    scanf("%d", &n);
    st.init(n);
    adj_list.resize(n);
    tin.resize(n);
    tout.resize(n);
    p.resize(n);
    ans.resize(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].first);
        p[i].second = i;
    }
    for (int i = 1; i < n; i++) {
        int b;
        scanf("%d", &b);
        b--;

        adj_list[b].pb(i);
    }

    dfs(0, -1);
    sort(p.begin(), p.end());
    reverse(p.begin(), p.end());

    for (int i = 0; i < n; i++) {
        // Find the ans for the current node
        int node = p[i].second;
        ans[node] = st.sum(tin[node], tout[node]);

        // And and the current node to the highs
        st.set(tin[node], 1);
    }

    for (int i = 0; i < n; i++)
        printf("%d\n", ans[i]);

    return 0;
}