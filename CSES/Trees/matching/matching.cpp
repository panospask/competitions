#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int n;
vector<int> dp[2];
vector<vector<int>> adj_list;

int calc_dp(int node, int par)
{
    // First calc the dp that would not include an edge to this node
    dp[0][node] = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh != par)
            dp[0][node] += calc_dp(neigh, node);
    }

    // Now try to also include this node if it is optimal
    dp[1][node] = dp[0][node];
    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            if (dp[0][node] - dp[1][neigh] + dp[0][neigh] + 1 > dp[1][node]) {
                dp[1][node] = dp[0][node] - dp[1][neigh] + dp[0][neigh] + 1;
            }
        }
    }

    return dp[1][node];
}

int main(void)
{
    scanf("%d", &n);
    dp[1].resize(n);
    dp[0].resize(n);
    adj_list.resize(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    printf("%d\n", calc_dp(0, -1));
    return 0;
}