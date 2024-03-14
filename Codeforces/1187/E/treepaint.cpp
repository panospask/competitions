#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

int n;
vector<vector<int>> adj_list;
vector<ll> dp_subtree;
vector<ll> dp_outside;
vector<ll> subtree_size;

void calculate_subtree(int node, int par)
{
    subtree_size[node] = 1;
    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;

        calculate_subtree(neigh, node);

        dp_subtree[node] += dp_subtree[neigh];
        subtree_size[node] += subtree_size[neigh];
    }

    dp_subtree[node] += subtree_size[node];
}

void calculate_outside(int node, int par)
{
    if (par == -1) {
        dp_outside[node] = 0;
    }
    else {
        dp_outside[node] = (dp_subtree[par] - subtree_size[node]) - dp_subtree[node] + dp_outside[par] + n - subtree_size[node];
    }

    for (auto neigh : adj_list[node]) if (neigh != par)
        calculate_outside(neigh, node);
}

int main(void)
{
    scanf("%d", &n);

    dp_subtree.assign(n, 0);
    dp_outside.assign(n, 0);
    subtree_size.assign(n, 0);
    adj_list.resize(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    calculate_subtree(0, -1);
    calculate_outside(0, -1);

    ll ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, dp_subtree[i] + dp_outside[i]);

    printf("%lld\n", ans);

    return 0;
}