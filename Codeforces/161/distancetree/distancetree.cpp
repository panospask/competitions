#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

int n, k;

vector<vector<int>> adj_list;
vector<vector<int>> dp;
ll ans = 0;

void dfs(int node, int par)
{
    for (auto neigh : adj_list[node])
        if (neigh != par)
            dfs(neigh, node);

    dp[node][0] = 1;
    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;

        for (int d = 0; d < k; d++) {
            ans += (ll)dp[node][k - (d + 1)] * dp[neigh][d];
        }
        for (int d = 0; d < k; d++) {
            dp[node][d + 1] += dp[neigh][d];
        }
    }
}

int main(void)
{
    scanf("%d %d", &n, &k);

    adj_list.resize(n);
    dp.assign(n, vector<int>(k + 1, 0));

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    dfs(0, -1);

    printf("%lld\n", ans);

    return 0;
}