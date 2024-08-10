#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const ll INF = 1e18;

int N;
vector<vector<int>> adj_list;
vector<int> t;
vector<int> h;

/* dp[i][start]:
 * The minimum tiredness to assign all edges in the subtree of i (inluding par[i]--i) to
 * a challenge.
 * 
 * start is a boolean variable denoting if the edge from node to par starts at node
 * or ends at node.
 */
vector<vector<ll>> dp;

void dfs(int node, int par)
{
    if (dp[node][0] != -INF || dp[node][1] != -INF) {
        return;
    }

    dp[node][0] = dp[node][1] = 0;
    int in = 0, out = 0;

    if (node != 0) {
        dp[node][0] = t[node];
    }

    vector<ll> c;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }
        
        dfs(neigh, node);

        if (h[node] < h[neigh]) {
            // Edge goes from node to neigh
            dp[node][0] += dp[neigh][false];
            out++;
        }
        else if (h[node] > h[neigh]) {
            // Edge goes from neigh to node
            dp[node][0] += dp[neigh][true];
            in++;
        }
        else {
            // Initially make them all out edges
            // And for each one calculate cost of making it in edge
            dp[node][0] += dp[neigh][0];
            c.push_back(dp[neigh][1] - dp[neigh][0]);
        }

        dp[node][0] += t[node];
    }
    dp[node][1] = dp[node][0];

    sort(c.begin(), c.end());

    ll reduction[2] = {0, 0};

    ll changecost = 0;
    for (int change = 0; change <= c.size(); change++) {
        reduction[0] = max(reduction[0], min((ll)out + (int)c.size() - change, (ll)in + (node != 0) + change) * t[node] - changecost);
        reduction[1] = max(reduction[1], min((ll)out + (node != 0) + (int)c.size() - change, (ll)in + change) * t[node] - changecost);

        if (change != c.size()) {
            changecost += c[change];
        }
    }

    dp[node][0] -= reduction[0];
    dp[node][1] -= reduction[1];

    if (node == 0) {
        assert(dp[node][0] == dp[node][1]);
    }

}

void read_input(void)
{
    scanf("%d", &N);

    t.resize(N);
    h.resize(N);
    adj_list.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &t[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &h[i]);
    }

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }
}

int main(void)
{
    read_input();

    dp.resize(N, vector<ll>(2, -INF));
    dfs(0, 0);

    printf("%lld\n", dp[0][0]);

    return 0;
}