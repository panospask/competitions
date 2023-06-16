#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

int n;
vector<int> l;
vector<int> r;
vector<vector<ll>> dp;
vector<vector<int>> adj_list;

void dfs(int node, int par)
{
    for (auto neigh : adj_list[node])
        if (neigh != par)
            dfs(neigh, node);

    for (int take = 0; take < 2; take++) {
        int v = take ? r[node] : l[node];

        dp[node][take] = 0;
        for (auto neigh : adj_list[node]) {
            if (neigh == par)
                continue;

            dp[node][take] += max(dp[neigh][false] + abs(l[neigh] - v), dp[neigh][true] + abs(r[neigh] - v));
        }
    }
}

void solve(void)
{
    dp.clear();
    adj_list.clear();
    l.clear();
    r.clear();

    scanf("%d", &n);

    adj_list.resize(n);
    l.resize(n);
    r.resize(n);
    dp.assign(n, vector<ll>(2, 0));

    for (int i = 0; i < n; i++)
        scanf("%d %d", &l[i], &r[i]);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    dfs(0, -1);

    printf("%lld\n", max(dp[0][false], dp[0][true]));
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}