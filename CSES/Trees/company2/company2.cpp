#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

struct segtree {

    int size;
    vector<ii> tree;

    void init(int n) {
        size = 1;
        while (size < n )
            size *= 2;

        tree.resize(size * 2);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = mp(a[lx], lx);
            else
                tree[x] = mp(INT_MAX, INT_MAX);
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

    ii get(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segment
            return mp(INT_MAX, INT_MAX);
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        auto n1 = get(l, r, 2 * x + 1, lx, mid);
        auto n2 = get(l, r, 2 * x + 2, mid, rx);

        return min(n1, n2);
    }
    ii get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

int n, q;
vector<vector<int>> adj_list;
vector<int> dist;
vector<int> latest_oc;
vector<int> eul_to_nodes;
vector<int> dist_in_eul;
segtree st;
int counter = 0;

void dfs(int node, int parent, int d)
{
    eul_to_nodes[counter] = node;
    dist[node] = d;
    dist_in_eul[counter] = d;
    latest_oc[node] = counter;
    counter++;

    for (auto neigh : adj_list[node])
        if (neigh != parent) {
            dfs(neigh, node, d + 1);
            eul_to_nodes[counter] = node;
            dist[node] = d;
            dist_in_eul[counter] = d;
            latest_oc[node] = counter;
            counter++;
        }

    return;
}


int main(void)
{
    scanf("%d %d", &n, &q);
    adj_list.resize(n);
    latest_oc.resize(n);
    eul_to_nodes.resize(2 * n + 1);
    dist_in_eul.resize(2 * n + 1);
    dist.resize(n);
    for (int i = 1; i < n; i++) {
        int b;
        scanf("%d", &b);
        b--;
        adj_list[b].pb(i);
        adj_list[i].pb(b);
    }
    dfs(0, -1, 0);
    st.init(2 * n + 1);
    st.build(dist_in_eul);

    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        int respos = st.get(min(latest_oc[a], latest_oc[b]), max(latest_oc[a], latest_oc[b]) + 1).second;
        printf("%d\n", eul_to_nodes[respos] + 1);
    }

    return 0;
}