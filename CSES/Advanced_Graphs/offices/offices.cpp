#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N, D;

// dp[node][d]: In the subtree of this node, what is the most amount of offices we can have,
// assuming the closest one is at least d-far
vector<deque<int>> dp;
vector<vector<int>> adj_list;

// Assuming we take the node, which is the "special" subtree and at what depth
vector<pi> special;

vector<int> ans;

void merge(deque<int>& a, deque<int>& b, int u, int v) {
    for (int l = 1; l < (min(a.size(), b.size())); l++) {
        int tmp = (D - l >= 0 && D - l < b.size()) ? b[D - l] : 0;
        int res = a[l] + tmp + 1;

        if (res > a[0]) {
            a[0] = res;
            special[u] = {v, D - l};
        }
    }

    if (a.size() < b.size()) {
        swap(a, b);
    }
    for (int l = 0; l < b.size(); l++) {
        a[l] = max(a[l], b[l]);
    }
}

void dfs(int node, int par) {
    dp[node].push_front(1);
    special[node] = {-1, -1};

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        dp[neigh].push_front(0);
        merge(dp[node], dp[neigh], node, neigh);
    }
}

void reconstruct(int node, int par, int t) {
    if (t == 0) {
        ans.push_back(node);
    }

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        if (t) {
            reconstruct(neigh, node, t - 1);
        }
        else {
            if (special[node].first == neigh) {
                reconstruct(neigh, node, special[node].second);
            }
            else {
                reconstruct(neigh, node, D - special[node].second);
            }
        }
    }
}

int main(void) {
    scanf("%d %d", &N, &D);

    adj_list.resize(N);
    special.resize(N);
    dp.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(0, -1);

    int t = 0;
    for (int i = 1; i < dp[0].size(); i++) {
        if (dp[0][i] > dp[0][t]) {
            t = i;
        }
    }

    printf("%d\n", (int)ans.size());
    for (auto u : ans) {
        printf("%d ", u + 1);
    }
    printf("\n");
}