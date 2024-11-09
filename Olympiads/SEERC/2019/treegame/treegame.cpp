#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<vector<int>> adj_list;

// dp[i]: If we try to match all vertices in the subtree of i, how many are left unmatched?
vector<int> dp;

void dfs(int node, int par)
{
    if (adj_list[node].size() == 1 && par != -1) {
        dp[node] = 1;
        return;
    }

    dp[node] = -1;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        dp[node] += dp[neigh];
    }

    if (dp[node] == -1) {
        dp[node] = 1;
    }
}

int main(void)
{
    scanf("%d", &N);

    adj_list.resize(N);
    dp.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    dfs(0, -1);

    if (dp[0] == 0) {
        printf("Bob\n");
    }
    else {
        printf("Alice\n");
    }

    return 0;
}