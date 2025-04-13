#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int subtask;
int N;
vector<int> f;
vector<vector<int>> adj_list;

vector<int> dist;

int bfs(int node) {
    queue<int> q;
    dist.assign(N, -1);
    dist[node] = 0;
    q.push(node);

    int opt = 0;
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front();
        cnt++;
        q.pop();
        opt = max(opt, dist[u]);

        for (auto neigh : adj_list[u]) {
            if (dist[neigh] == -1) {
                dist[neigh] = dist[u] + 1;
                q.push(neigh);
            }
            else if (dist[neigh] != dist[u] - 1) {
                return 0;
            }
        }
    }

    if (cnt != N) {
        return 0;
    }
    return opt;
}

int main(void) {
    scanf("%d", &subtask);

    scanf("%d", &N);
    
    f.resize(N);
    adj_list.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &f[i]);
        f[i]--;

        adj_list[f[i]].pb(i);
        adj_list[i].pb(f[i]);
    }

    for (int i = 0; i < N; i++) {

        adj_list[i].erase(find(adj_list[i].begin(), adj_list[i].end(), f[i]));
        adj_list[f[i]].erase(find(adj_list[f[i]].begin(), adj_list[f[i]].end(), i));

        int ans = 0;
        for (int j = 0; j < N; j++) {
            ans = max(ans, bfs(j));
        }

        adj_list[i].pb(f[i]);
        adj_list[f[i]].pb(i);

        if (ans == 0) {
            printf("-1\n");
        }
        else {
            printf("%d\n", ans + 1);
        }
    }

    return 0;
}