#include <bits/stdc++.h>
#define MOD ((int)1e9 + 7)
#define pb push_back

using namespace std;

int n;
//dp[i][k]: The total number of ways the subtree of i can be painted
// k = 0: i is black
// k = 1: i is white
vector<vector<long long>> dp;
vector<vector<int>> adj_list;

void calc_dp(int node, int par)
{
    if (adj_list[node].empty()) {
        dp[node][0] = dp[node][1] = 1;
        return;
    }

    // First calculate how many ways there are to paint the node black
    dp[node][0] = 1;
    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            calc_dp(neigh, node);
            dp[node][0] = (dp[node][0] * dp[neigh][1]) % MOD;
        }
    }

    // Then white
    dp[node][1] = 1;
    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            dp[node][1] = (dp[node][1] * (dp[neigh][0] + dp[neigh][1])) % MOD;
        }
    }
}

int main(void)
{
    scanf("%d", &n);
    adj_list.resize(n);
    dp.resize(n, vector<long long>(2));
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    calc_dp(0, -1);
    long long ans = (dp[0][0] + dp[0][1]) % MOD;
    printf("%lld\n", ans);

    return 0;
}