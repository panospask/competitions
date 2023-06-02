#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int n, m;
vector<vector<int>> adj_list;
vector<int> topsort;
vector<bool> visited;
vector<int> dp;
vector<int> pcity;

void dfs(int node)
{
    if (visited[node])
        return;

    // No need to check for cycles since it's guaranteed by the input that no cycles exist
    visited[node] = true;
    for (auto neigh : adj_list[node])
        dfs(neigh);

    topsort.pb(node);
}

int main(void)
{
    scanf("%d %d", &n, &m);

    adj_list.resize(n);
    visited.assign(n, false);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
    }

    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs(i);
    reverse(topsort.begin(), topsort.end());

    dp.assign(n, -1);
    pcity.assign(n, -1);

    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        int curcity = topsort[i];

        if (dp[curcity] == -1)
            continue;

        for (auto neigh : adj_list[curcity])
            if (dp[neigh] < dp[curcity] + 1) {
                dp[neigh] = dp[curcity] + 1;
                pcity[neigh] = curcity;
            }
    }

    if (dp[n - 1] == -1) {
        printf("IMPOSSIBLE\n");
    }
    else {
        stack<int> ans;
        for (int node = n - 1; node != -1; node = pcity[node]) {
            ans.push(node);
        }

        printf("%d\n", (int)ans.size());
        while (!ans.empty()) {
            printf("%d ", ans.top() + 1);
            ans.pop();
        }
        printf("\n");
    }

    return 0;
}