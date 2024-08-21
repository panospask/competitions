#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int SMALL = -1;
const int NOTHING = 0;
const int BIG = 1;

int N, M;
vector<vector<pi>> adj_list;

/* dp[node]:
 * The minimum and maximum value that we are allowed to give to node
 * when considering only the subtree of node
 */
vector<pi> dp;

vector<bool> allowed;

bool dfs(int node, int par)
{
    dp[node] = {1, M};

    vector<int> banned;
    for (auto [neigh, op] : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        bool good = dfs(neigh, node);
        if (!good) {
            return false;
        }

        if (op == SMALL) {
            // Neigh must be smaller than this node
            dp[node].first = max(dp[node].first, dp[neigh].first + 1);
        }
        else if (op == BIG) {
            // Neigh must be bigger than this one
            dp[node].second = min(dp[node].second, dp[neigh].second - 1);
        }
        else {
            // Neigh must have a value different to node
            if (dp[neigh].first == dp[neigh].second) {
                banned.pb(dp[neigh].first);
            }
        }
    }

    for (auto b : banned) {
        allowed[b] = false;
    }

    while (dp[node].first <= N && allowed[dp[node].first] == false) {
        dp[node].first++;
    }
    while (dp[node].second >= 1 && allowed[dp[node].second] == false) {
        dp[node].second--;
    }

    for (auto b : banned) {
        allowed[b] = true;
    }

    return dp[node].first <= dp[node].second;
}

bool possible(int x)
{
    M = x;
    allowed.assign(N + 1, true);
    return dfs(0, 0);
}

void solve(void)
{
    scanf("%d", &N);

    adj_list.assign(N, vector<pi>());
    dp.assign(N, {1, N});

    for (int i = 0; i < N - 1; i++) {
        int u, v, op;
        scanf("%d %d %d", &u, &v, &op);
        u--; v--;

        if (op == 0) {
            adj_list[u].pb(mp(v, NOTHING));
            adj_list[v].pb(mp(u, NOTHING));
        }
        else {
            adj_list[u].pb(mp(v, BIG));
            adj_list[v].pb(mp(u, SMALL));
        }
    }

    int l = 1;
    int r = N;

    while (l + 1 < r) {
        int mid = (l + r) / 2;

        if (possible(mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    printf("%d\n", r);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    
    while (t--) {
        solve();
    }

    return 0;
}