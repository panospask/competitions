#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

const int INF = INT_MAX;

int n, q;
vector<vector<int>> adj_list;
vector<int> euler_height;
vector<int> first;
vector<int> dist;
int counter = 0;

struct segtree {

    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;
        tree.resize(2 * size);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = a[lx];
            else
                tree[x] = INF;
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    int get(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return INF;
        }
        if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        auto n1 = get(l, r, 2 * x + 1, lx, mid);
        auto n2 = get(l, r, 2 * x + 2, mid, rx);

        return min(n1, n2);
    }
    int get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

void dfs(int node, int par, int d)
{
    dist[node] = d;
    first[node] = counter;
    euler_height[counter] = dist[node];
    counter++;

    for (auto neigh : adj_list[node])
        if (neigh != par) {
            dfs(neigh, node, d + 1);
            euler_height[counter++] = dist[node];
        }

    return;
}

segtree st;

int main(void)
{
    scanf("%d %d", &n, &q);
    st.init(2 * n - 1);
    adj_list.resize(n);
    euler_height.resize(2 * n - 1);
    dist.resize(n);
    first.resize(n);
    counter = 0;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    dfs(0, -1, 0);
    st.build(euler_height);

    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        int v1 = first[a], v2 = first[b];
        if (v1 > v2)
            swap(v1, v2);

        int lca = st.get(v1, v2 + 1);
        int ans = dist[a] + dist[b] - 2 * lca;
        printf("%d\n", ans);
    }

    return 0;
}