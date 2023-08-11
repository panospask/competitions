#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

struct BITree {
    int size;
    vector<int> tree;

    void init(int n) {
        size = n;
        tree.assign(size, 0);
    }

    void add(int i, int v) {
        for (int x = i; x < size; x = x | (x + 1))
            tree[x] += v;
    }

    int get(int i) {
        int res = 0;
        for (int x = min(i, size - 1); x >= 0; x = (x & (x + 1)) - 1)
            res += tree[x];
        return res;
    }
    int get(int l, int r) {
        return get(r) - get(l - 1);
    }
};

BITree b;
int k1, k2;
int N, K;
vector<bool> removed;
vector<int> subtree_size;
vector<vector<int>> adj_list;
vector<int> dist;

int get_subtree_size(int node, int par, int d)
{
    subtree_size[node] = 1;
    dist.pb(d);

    for (auto neigh : adj_list[node]) {
        if (removed[neigh] || neigh == par)
            continue;

        subtree_size[node] += get_subtree_size(neigh, node, d + 1);
    }

    return subtree_size[node];
}

int calculate_centroid(int node, int par, int sz)
{
    for (auto neigh : adj_list[node]) {
        if (neigh == par || removed[neigh])
            continue;

        if (subtree_size[neigh] >= sz / 2)
            return calculate_centroid(neigh, node, sz);
    }

    return node;
}

ll centroid_decompose(int node)
{
    int maxsz = subtree_size[node] / 2 + 2;
    int c = calculate_centroid(node, -1, subtree_size[node]);

    removed[c] = true;
    b.add(0, 1);


    ll res = 0;
    for (auto neigh : adj_list[c]) {
        if (!removed[neigh]) {
            dist.clear();
            get_subtree_size(neigh, -1, 1);

            // Count # of paths AT MOST k2 and AT LEAST k1
            for (auto d : dist) {
                int maxv = k2 - d;
                int minv = k1 - d;
                res += b.get(minv, maxv);
            }
            for (auto d : dist)
                b.add(d, 1);
        }
    }

    for (int i = 0; i <= maxsz; i++)
        b.add(i, -b.get(i));

    for (auto neigh : adj_list[c]) {
        if (!removed[neigh]) {
            res += centroid_decompose(neigh);
        }
    }

    return res;
}

int main(void)
{

    scanf("%d %d %d", &N, &k1, &k2);

    adj_list.resize(N);
    subtree_size.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    ll ans = 0;

    b.init(N);
    removed.assign(N, false);
    get_subtree_size(0, -1, 0);
    ans += centroid_decompose(0);

    printf("%lld\n", ans);
}