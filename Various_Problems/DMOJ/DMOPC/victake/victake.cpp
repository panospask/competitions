#include <bits/stdc++.h>
#define pb push_back
#define CHECK_BIT(var, pos) ((var) & (1 << pos))

using namespace std;

const int MAXN = 5e5;
const int MAXANC = 20;

struct SegTree {
    int size;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
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
        if (i < mid) {
            add(i, v, 2 * x + 1, lx, mid);
        }
        else {
            add(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        
        return calc(l, r, 2 * x + 1, lx, mid) + calc(l, r, 2 * x + 2, mid, rx);
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N, K, M;
vector<int> adj_list[MAXN];
set<int> assigned[MAXN];  
int ancestors[MAXANC][MAXN];
int c[MAXN];
int dep[MAXN], tin[MAXN], tout[MAXN], trav[MAXN];
int counter = 0;
SegTree st;

int jump(int a, int v)
{
    for (int up = 0; up < MAXANC; up++) {
        if (CHECK_BIT(v, up)) {
            a = ancestors[up][a];
        }
    }

    return a;
}

int lca(int a, int b)
{
    if (dep[a] < dep[b]) {
        swap(a, b);
    }

    a = jump(a, dep[a] - dep[b]);
    if (a == b) {
        return a;
    }

    for (int up = MAXANC - 1; up >= 0; up--) {
        int n_a = ancestors[up][a];
        int n_b = ancestors[up][b];

        if (n_a != n_b) {
            a = n_a;
            b = n_b;
        }
    }

    return ancestors[0][a];
}

void dfs(int node, int par)
{
    trav[counter] = node;
    tin[node] = counter++;
    dep[node] = dep[par] + 1;
    ancestors[0][node] = par;

    for (auto kid : adj_list[node]) {
        if (kid != par) {
            dfs(kid, node);
        }
    }

    tout[node] = counter;
}

// m = -1: Remove city
// m = 1: Insert city
void modify_city(int guard, int city, int m)
{
    int nxt = -1, prv = -1;
    int l1, l2;
    auto it = assigned[guard].upper_bound(tin[city]);

    if (it != assigned[guard].end()) {
        nxt = *it;
    }
    if (it != assigned[guard].begin()) {
        it--;
        prv = *it;
    }

    st.add(tin[city], 1 * m);
    if (prv != -1) {
        prv = trav[prv];
        l1 = lca(prv, city);
        st.add(tin[l1], -1 * m);
    }
    if (nxt != -1) {
        nxt = trav[nxt];
        l2 = lca(nxt, city);
        st.add(tin[l2], -1 * m);
    }
    if (prv != -1 && nxt != -1) {
        st.add(min(tin[l1], tin[l2]), 1 * m);
    }
}

void precalculate_ancestors(void)
{   
    dep[0] = -1;
    dfs(0, 0);

    for (int up = 1; up < MAXANC; up++) {
        for (int i = 0; i < N; i++) {
            ancestors[up][i] = ancestors[up - 1][ancestors[up - 1][i]];
        }
    }
}

int main(void)
{
    scanf("%d %d %d", &N, &K, &M);

    st.init(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &c[i]);    
        c[i]--;
    }

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    precalculate_ancestors();

    for (int i = 0; i < N; i++) {
        int cur = trav[i];    

        st.add(tin[cur], 1);
        if (assigned[c[cur]].size() > 0) {
            st.add(tin[lca(cur, trav[*assigned[c[cur]].rbegin()])], -1);
        }

        assigned[c[cur]].insert(assigned[c[cur]].end(), tin[cur]);
    }

    while (M--) {
        int op, city;
        scanf("%d %d", &op, &city);
        city--;

        if (op == 1) {
            int guard;
            scanf("%d", &guard);
            guard--;

            // Remove city from previous guard
            assigned[c[city]].erase(tin[city]);
            modify_city(c[city], city, -1);

            // Insert city to new guard
            modify_city(guard, city, 1);
            assigned[guard].insert(tin[city]);
            c[city] = guard;
        }
        if (op == 2) {
            printf("%d\n", st.calc(tin[city], tout[city]));
        }
    }

    return 0;
}