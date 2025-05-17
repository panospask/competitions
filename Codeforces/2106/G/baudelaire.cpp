#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<vector<int>> adj_list;
vector<int> f;
vector<int> values;

vector<int> subtree;

void toggle(int i) {
    printf("? 2 %d\n", i + 1);
    fflush(stdout);
}

int query(vector<int> v) {
    printf("? 1 %d", (int)v.size());
    for (auto i : v) {
        printf(" %d", i + 1);
    }
    printf("\n");
    fflush(stdout);

    int res;
    scanf("%d", &res);

    return res;
}

void dfs(int node, int par) {
    subtree[node] = 1;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        subtree[node] += subtree[neigh];
    }
}

int find_centroid(int node, int par, int size) {
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        if (subtree[neigh] > size / 2) {
            return find_centroid(neigh, node, size);
        }
    }

    return node;
}

int calculate_root(int node) {
    dfs(node, -1);
    int cen = find_centroid(node, -1, subtree[node]);

    toggle(cen);

    int l = 0;
    int r = adj_list[cen].size() + 1;
    while (l + 1 < r) {
        int mid = (l + r ) / 2;

        vector<int> v(adj_list[cen].begin(), adj_list[cen].begin() + mid);

        int sum = 0;
        for (auto i : v) {
            sum += f[i];
        }

        int res = query(v);
        if (abs(res - sum) != 2 * mid) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    toggle(cen);

    if (l == adj_list[cen].size()) {
        return cen;
    }

    int nxt = adj_list[cen][r - 1];
    adj_list[nxt].erase(find(adj_list[nxt].begin(), adj_list[nxt].end(), cen));
    int ans = calculate_root(nxt);
    adj_list[nxt].pb(cen);

    return ans;
}

void propagate_answer(int node, int par) {
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        values[neigh] = f[neigh] - f[node];
        propagate_answer(neigh, node);
    }
}

void solve(void) {
    scanf("%d", &N);

    f.assign(N, 0);
    adj_list.assign(N, vector<int>());
    subtree.assign(N, 0);
    values.assign(N, 0);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    for (int i = 0; i < N; i++) {
        f[i] = query({i});
    }

    int root = calculate_root(0);

    values[root] = f[root];
    propagate_answer(root, -1);

    printf("!");
    for (int i = 0; i < N; i++) {
        printf(" %d", values[i]);
    }
    printf("\n");
    fflush(stdout);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}