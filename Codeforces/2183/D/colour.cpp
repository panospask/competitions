#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

int N;
vector<vector<int>> adj_list;
vector<int> par;
vector<int> depth;

vector<vector<int>> at_d;

// At which point do we perform the operation on node i
vector<int> point;

vector<vector<int>> operations;

void dfs(int node) {
    if (node) {
        adj_list[node].erase(find(adj_list[node].begin(), adj_list[node].end(), par[node]));
    }

    at_d[depth[node]].pb(node);
    for (auto neigh : adj_list[node]) {
        if (neigh == par[node]) {
            continue;
        }

        par[neigh] = node;
        depth[neigh] = depth[node] + 1;
        dfs(neigh);
    }
}

void solve(void) {
    scanf("%d", &N);
    
    adj_list.assign(N, vector<int>());
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    par.assign(N, -1);
    depth.assign(N, 0);
    at_d.assign(N, vector<int>());
    
    dfs(0);
    
    int ans = 2;
    for (auto cur : at_d) {
        int c = 1;
        for (int i = 1; i < cur.size(); i++) {
            c = c && par[cur[i - 1]] == par[cur[i]];
        }
        
        ans = max(ans, (int)cur.size() + c);
    }
    
    operations.assign(ans, vector<int>());
    point.assign(N, -1);

    point[0] = 0;
    operations[0].pb(0);

    vector<bool> used(ans, false);
    used[0] = true;

    for (int d = 1; d < N; d++) {
        // Sample kids from each kid-having node
        vector<int> kids;
        int cur = 0;
        for (auto node : at_d[d]) {
            if (point[node] == -1) {
                while (used[cur]) {
                    cur++;
                }
                point[node] = cur;
                cur++;
            }

            operations[point[node]].pb(node);
            if (!adj_list[node].empty()) {
                kids.pb(adj_list[node][0]);
            }
        }

        if (kids.size() >= 2) {
            for (int i = 1; i < kids.size(); i++) {
                point[kids[i]] = point[par[kids[i - 1]]];
            }
            point[kids[0]] = point[par[kids.back()]];
        }

        for (auto node : at_d[d - 1]) {
            used[point[node]] = false;
        }
        for (auto node : at_d[d]) {
            if (!adj_list[node].empty()) {
                used[point[node]] = true;
            }
        }
    }


    printf("%d\n", ans);

    for (auto o : operations) {
        printf("%d ", (int)o.size());
        for (auto p : o) {
            printf("%d ", p + 1);
        }
        printf("\n");
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}