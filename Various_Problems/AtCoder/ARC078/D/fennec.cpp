#include <bits/stdc++.h>

using namespace std;

const int INF = 1e6;

int N;
vector<vector<int>> adj_list;
vector<int> sourcedist;
vector<int> targetdist;
vector<int> subtree_size;
int ans[2];

void dfs(int node, int par, int target)
{
    if (node != par) {
        sourcedist[node] = sourcedist[par] + 1;
    }
    if (node == target) {
        targetdist[node] = 0;
    }

    subtree_size[node] = 1;
    for (auto kid : adj_list[node]) {
        if (kid != par) {
            dfs(kid, node, target);
            subtree_size[node] += subtree_size[kid];

            if (targetdist[kid] != INF) {
                targetdist[node] = targetdist[kid] + 1;
            }
        }
    }

    if (targetdist[node] != INF) {
        // Node is in the path from source to target
        int winner;
        if (sourcedist[node] <= targetdist[node]) {
            // Black wins
            winner = 0;
        }
        else {
            // White wins
            winner = 1;
        }

        ans[winner]++;
        for (auto kid : adj_list[node]) {
            if (kid != par && targetdist[kid] == INF) {
                ans[winner] += subtree_size[kid];
            }   
        }
    }
}

int main(void)
{
    scanf("%d", &N);

    adj_list.resize(N);
    subtree_size.assign(N, 0);
    sourcedist.assign(N, INF);
    targetdist.assign(N, INF);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    sourcedist[0] = 0;
    dfs(0, 0, N - 1);
    
    if (ans[0] > ans[1]) {
        printf("Fennec\n");
    }
    else {
        printf("Snuke\n");
    }

    return 0;
}