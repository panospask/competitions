#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const ll INF = 1e17;

int N;
vector<vector<pi>> adj_list;
vector<int> d;

/* dp[node][avail]:
 * Select maximum value of edges in the subtree of node.
 * avail is a variable denoting if we can take the edge par--node or not.
 */
vector<vector<ll>> dp;

void dfs(int node, int par)
{
    ll res = 0;

    vector<ll> possible;
    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);

        res += dp[neigh][0];
        
        // How much do we benefit from taking the edge neigh--node
        ll ben = w + dp[neigh][1] - dp[neigh][0];
        possible.pb(ben);
    }

    dp[node][0] = res;
    if (d[node] == 0) {
        dp[node][1] = -INF;
        return;
    }

    dp[node][1] = dp[node][0];
    sort(possible.rbegin(), possible.rend());
    for (int i = 0; i < d[node] - 1; i++) {
        dp[node][0] += max(0LL, possible[i]);
        dp[node][1] += max(0LL, possible[i]);
    }

    if (d[node] < adj_list[node].size() || node == 0) {
        dp[node][0] += max(0LL, possible[d[node] - 1]);
    }
}

int main(void)
{
    scanf("%d", &N);

    d.resize(N);
    adj_list.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(mp(v, w));
        adj_list[v].pb(mp(u, w));
    }

    dp.resize(N, vector<ll>(2));

    dfs(0, 0);

    printf("%lld\n", dp[0][0]);

    return 0;
}