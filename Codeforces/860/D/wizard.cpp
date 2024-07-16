#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N, M;
vector<vector<int>> adj_list;
vector<bool> visited;
vector<bool> remained;
vector<bool> completed;
vector<vector<int>> episodes;

void dfs(int node, int par)
{
    visited[node] = true;

    vector<int> uniting;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }
        else if (visited[neigh]) {
            if (!completed[neigh]) {
                // Neigh is an ancestor in the dfs tree
                uniting.pb(neigh);
            }
        }
        else {
            dfs(neigh, node);

            if (remained[neigh]) {
                uniting.pb(neigh);
            }
        }
    }

    if (uniting.size() % 2 == 1) {
        remained[node] = false;
        if (par != node) {
            uniting.pb(par);
        }
        else {
            uniting.pop_back();
        }
    }
    else {
        remained[node] = true;
    }

    for (int i = 0; i < uniting.size(); i += 2) {
        episodes.pb({uniting[i], node, uniting[i + 1]});
    }

    completed[node] = true;
}

int main(void)
{
    scanf("%d %d", &N, &M);

    remained.resize(N);
    visited.assign(N, false);
    completed.assign(N, false);
    adj_list.resize(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            dfs(i, i);
        }
    }

    printf("%d\n", (int)episodes.size());
    for (int i = 0; i < episodes.size(); i++) {
        printf("%d %d %d\n", episodes[i][0] + 1, episodes[i][1] + 1, episodes[i][2] + 1);
    }

    return 0;
}