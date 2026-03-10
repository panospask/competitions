#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int INF = 1e6;

int N, K, s;
vector<vector<int>> adj_list;

// Smallest distance to winning node
vector<int> smallest;

void dfs(int node, int par) {
    int cnt = 0;

    if (adj_list[node].size() == 1) {
        smallest[node] = 0;
    }

    int m2 = INF;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);

        if (smallest[neigh] + 1 < smallest[node]) {
            m2 = smallest[node];
            smallest[node] = 1 + smallest[neigh];
        }
        else if (smallest[neigh] + 1 < m2) {
            m2 = smallest[neigh] + 1;
        }
    }

    if (smallest[node] - 1 + m2 <= K) {
        smallest[node] = 0;
    }
}

void solve(void) {
    scanf("%d %d %d", &N, &K, &s);
    s--;

    adj_list.assign(N, vector<int>());
    smallest.assign(N, INF);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    dfs(s, -1);

    if (smallest[s] == 0) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}