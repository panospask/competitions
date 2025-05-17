#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, R, K, L;

ll ans = 0;
vector<int> A;
vector<vector<int>> adj_list;

vector<int> cnt;
vector<ll> subtree;

vector<ll> best;

void dfs(int node, int par) {
    cnt[node] = 1;
    subtree[node] = A[node];

    best[node] = 0;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        ans = max(ans, best[node] + best[neigh]);
        best[node] = max(best[node], best[neigh]);
        subtree[node] += subtree[neigh];
        cnt[node] += cnt[neigh];
    }

    best[node] = max(best[node], subtree[node]);
}

int main(void) {
    scanf("%d %d %d %d", &N, &R, &K, &L);
    R--;

    adj_list.resize(N);
    A.resize(N);
    best.resize(N);
    subtree.resize(N);
    cnt.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(R, -1);

    printf("%lld\n", ans);

    return 0;
}