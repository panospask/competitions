#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MOD ((int)1e9 + 7)

using namespace std;

typedef long long ll;

int n, k;
vector<vector<int>> adj_list;
vector<vector<ll>> dp;
vector<int> coloured;

void dfs(int node, int par)
{
    for (auto neigh : adj_list[node])
        if (neigh != par)
            dfs(neigh, node);

    dp[node][0] = dp[node][1] = dp[node][2] = 0;
    if (coloured[node] == -1) {
        dp[node][0] = dp[node][1] = dp[node][2] = 1;
    }
    else {
        dp[node][coloured[node]] = 1;
    }

    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;

        for (int c = 0; c < 3; c++) {
            dp[node][c] *= (dp[neigh][(c+1)%3] + dp[neigh][(c+2)%3]);
            dp[node][c] %= MOD;
        }
    }
}

int main(void)
{
    freopen("barnpainting.in", "r", stdin);
    freopen("barnpainting.out", "w", stdout);

    scanf("%d %d", &n, &k);
    adj_list.resize(n);
    dp.resize(n, vector<ll>(3));
    coloured.assign(n, -1);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }
    for (int i = 0; i < k; i++) {
        int a, c;
        scanf("%d %d", &a, &c);
        a--; c--;

        coloured[a] = c;
    }

    dfs(0, -1);

    ll ans = dp[0][0] + dp[0][1] + dp[0][2];
    ans %= MOD;

    printf("%lld\n", ans);

    return 0;
}