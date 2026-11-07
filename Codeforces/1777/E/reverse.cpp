#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

const int MAXW = 1e9;

int N, M;
vector<vector<pi>> adj_list;

vector<bool> visited;
vector<int> s;

void dfs1(int node, int x) {
    if (visited[node]) {
        return;
    }

    visited[node] = true;
    for (auto [neigh, w] : adj_list[node]) {
        if (w <= x) {
            dfs1(neigh, x);
        }
    }
    s.push_back(node);
}

int dfs2(int node, int x) {
    if (visited[node]) {
        return 0;
    }

    visited[node] = true;
    int res = 1;
    for (auto [neigh, w] : adj_list[node]) {
        if (w <= x) {
            res += dfs2(neigh, x);
        }
    }

    return res;
}

bool possible(int x) {
    s.clear();
    
    visited.assign(N, false);
    for (int i = 0; i < N; i++) {
        dfs1(i, x);
    }
    visited.assign(N, false);
    int res = dfs2(s.back(), x);
    return res == N;
}

void solve(void) {
    scanf("%d %d", &N, &M);

    adj_list.assign(N, vector<pi>());
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].push_back({v, 0});
        adj_list[v].push_back({u, w});
    }

    int l = -1;
    int r = MAXW + 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (possible(mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    if (r == MAXW + 1) {
        printf("-1\n");
    }
    else {
        printf("%d\n", r);
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}