#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e9;

int N;
vector<vector<pi>> adj_list;
vector<int> dist;

int L, R;
vector<int> s;
vector<vector<int>> idx;

int dfs(int node, int par) {
    int ans = -INF;
    auto it = lower_bound(idx[node].begin(), idx[node].end(), L);
    if (it != idx[node].end() && *it <= R) {
        ans = dist[node];
    }

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dist[neigh] = dist[node] + w;
        ans = max(ans, dfs(neigh, node));
    }

    return ans;
}

int main(void) {
    scanf("%d", &N);
    
    adj_list.resize(N);
    idx.resize(N);
    dist.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].push_back({v, w});
        adj_list[v].push_back({u, w});
    }

    int Q;
    scanf("%d", &Q);
    int last = 0;
    while (Q--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int u;
            scanf("%d", &u);
            u = (u ^ abs(last)) % N + 1;
            u--;

            s.push_back(u);
            idx[u].push_back(s.size());
        }
        else if (op == 2) {
            idx[s.back()].pop_back();
            s.pop_back();
        }
        else {
            int l, r, u;
            scanf("%d %d %d", &l, &r, &u);
            
            u = (u ^ abs(last)) % N + 1;
            
            u--;

            
            l = (l ^ abs(last)) % s.size() + 1;
            r = (r ^ abs(last)) % s.size() + 1;
            L = min(l, r);
            R = max(l, r);

            dist[u] = 0;
            last = dfs(u, -1);
            printf("%d\n", last);
        }
    }

    return 0;
}