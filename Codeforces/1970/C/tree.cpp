#include <bits/stdc++.h>

using namespace std;

int N, T;
vector<vector<int>> adj_list;

// Number of LOSING children
vector<int> cnt;

vector<bool> lost;

void dfs(int node, int par) {
    cnt[node] = 0;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        cnt[node] += lost[neigh];
    }

    lost[node] = (cnt[node] == 0);
}

void reroot(int node, int par, int v) {
    cnt[node] += v;

    lost[node] = (cnt[node] == 0);

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        int curcnt = cnt[node] - lost[neigh];
        reroot(neigh, node, curcnt == 0);
    }
}

int main(void) {
    scanf("%d %d", &N, &T);

    adj_list.resize(N);
    cnt.resize(N);
    lost.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(0, -1);
    reroot(0, -1, 0);

    while (T--) {
        int u;
        scanf("%d", &u);
        u--;

        if (!lost[u]) {
            printf("Ron\n");
        }
        else {
            printf("Hermione\n");
        }
    }
}