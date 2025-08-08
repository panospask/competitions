#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

int N, K;
vector<vector<int>> adj_list;
vector<int> c, w;
vector<set<int>> colors;

ll ans = 0;

// 0 = safe, -1 = fail
int merge(set<int>& a, set<int>& b) {
    int ans = 0;
    for (auto col : b) {
        if (a.count(col)) {
            if (ans == 0) {
                ans = col;
            }
            else {
                ans = -1;
            }
        }
        else {
            a.insert(col);
        }
    }

    return ans;
}

void dfs(int node, int par) {
    int res = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        if (colors[node].size() < colors[neigh].size()) {
            swap(colors[node], colors[neigh]);
        }
        int cur = merge(colors[node], colors[neigh]);
        if (cur != 0) {
            if (res == 0) {
                res = cur;
            }
            else if (res != cur) {
                res = -1;
            }
        }
    }

    if (res != 0) {
        if (res == -1) {
            ans += w[node];
        }
        else if (c[node] != 0 && res != c[node]) {
            ans += w[node];
        }
        else {
            c[node] = res;
        }
    }
    if (c[node] == 0 && colors[node].size() >= 1) {
        c[node] = *colors[node].begin();
    }
    if (c[node] != 0) {
        colors[node].insert(c[node]);
    }
}

void propagate(int node, int par) {
    if (c[node] == 0) {
        c[node] = c[par];
    }

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        propagate(neigh, node);
    }
}

void solve(void) {
    scanf("%d %d", &N, &K);
    
    adj_list.clear();
    adj_list.resize(N);
    colors.clear();
    colors.resize(N);
    c.resize(N);
    w.resize(N);
    ans = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &w[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &c[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    dfs(0, -1);
    if (c[0] == 0) {
        c[0] = 1;
    }
    propagate(0, -1);

    printf("%lld\n", ans);
    for (int i = 0; i < N; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}