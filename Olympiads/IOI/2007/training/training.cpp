#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

typedef pair<int, int> pi;

struct Edge {
    int e1, e2;
    int id;
    int cost;
    
    int added_value;
    int node_bitmask;
};

int N, M;

vector<vector<pi>> adj_list;
vector<Edge> edges;
vector<vector<int>> kids;

// Variables used for dfs
int counter;
vector<int> dep;
vector<int> tin, tout, trav;
vector<set<int>> unfinished;

/* paths[i]: A list of the ids of non tree edges that have  i as the node with the highest
 * depth on the tree path between endpoints.
 */
vector<vector<int>> paths;

/* dp[i][mask]: Max cost of unpaved edges that can remain unblocked in the subtree of i, given that we have removed
 * the kids of i denoted by mask
 */
vector<vector<int>> dp;

/* follow[i][j]: The position of the next node on the path from i to j in the kids list of i
 * Only valid when i is an ancestor of j
 */
vector<vector<int>> follow;

void insert_unfinished(int node, int edge_id)
{
    if (unfinished[node].count(edge_id)) {
        // The other endpoint of the edge is also found
        unfinished[node].erase(edge_id);

        // Test if the path is of even length (so the cycle formed is of odd length) and can be inserted into paths
        int len = dep[edges[edge_id].e1] + dep[edges[edge_id].e2] - 2 * dep[node];

        if (len % 2 == 0) {
            paths[node].pb(edge_id);
        }
    }
    else {
        unfinished[node].insert(edge_id);
    }
}

void dfs(int node, int par)
{
    trav[counter] = node;
    tin[node] = counter;
    counter++;

    for (auto [neigh, id] : adj_list[node]) {
        if (neigh == par) {
            continue;
        }
        else if (edges[id].cost == 0) {
            // Actual child of node in the paved tree
            dep[neigh] = dep[node] + 1;
            kids[node].pb(neigh);
            dfs(neigh, node);

            for (int t = tin[neigh]; t < tout[neigh]; t++) {
                follow[node][trav[t]] = kids[node].size() - 1;
            }
        }
        else {
            // This is not an actual child of node, insert it into unfinished paths to find the lca between node and neigh
            unfinished[node].insert(id);
        }
    }

    for (auto kid : kids[node]) {
        if (unfinished[kid].size() > unfinished[node].size()) {
            swap(unfinished[kid], unfinished[node]);
        }
        for (auto id : unfinished[kid]) {
            insert_unfinished(node, id);
        }
    }

    tout[node] = counter;
}

int calc_path(int node, int target)
{
    int res = 0;
    while (node != target) {
        int tot = kids[node].size();
        int nxt = follow[node][target];

        res += dp[node][(1 << tot) - 1 - (1 << nxt)];
        node = kids[node][nxt];
    }
    res += dp[target].back();

    return res;
}

void calculate_dp(int node)
{
    dp[node].assign(1 << kids[node].size(), 0);

    for (auto kid : kids[node]) {
        calculate_dp(kid);
    }

    // Find the added value of all paths
    for (auto id : paths[node]) {
        edges[id].added_value = edges[id].cost;
        

        int tot = 0;
        if (edges[id].e1 != node) {
            int nxt = follow[node][edges[id].e1];
            edges[id].added_value += calc_path(kids[node][nxt], edges[id].e1);
            tot += (1 << nxt);
        }
        if (edges[id].e2 != node) {
            int nxt = follow[node][edges[id].e2];
            edges[id].added_value += calc_path(kids[node][nxt], edges[id].e2);
            tot += (1 << nxt);
        }

        edges[id].node_bitmask = tot;
    }

    for (int mask = 0; mask < (1 << kids[node].size()); mask++) {
        for (auto id : paths[node]) {
            if ((edges[id].node_bitmask & mask) == edges[id].node_bitmask) {
                int res = edges[id].added_value + dp[node][mask - edges[id].node_bitmask];
                dp[node][mask] = max(dp[node][mask], res);
            }
        }

        // What if we add no edge and simply calculate all the subtrees
        int res = 0;
        for (int i = 0; i < kids[node].size(); i++) {
            if (CHECK_BIT(mask, i)) {
                res += dp[kids[node][i]].back();
            }
        }
        dp[node][mask] = max(dp[node][mask], res);
    }
}

int main(void)
{
    scanf("%d %d", &N, &M);

    counter = 0;
    dp.resize(N);
    dep.resize(N);
    tin.resize(N);
    tout.resize(N);
    trav.resize(N);
    follow.resize(N, vector<int>(N));
    unfinished.resize(N);
    paths.resize(N);
    adj_list.resize(N);
    kids.resize(N);
    edges.resize(M);

    int tot = 0;
    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        a--; b--;

        tot += c;
        edges[i] = {a, b, i, c, 0, 0};

        adj_list[a].pb(mp(b, i));
        adj_list[b].pb(mp(a, i));
    }

    dep[0] = 0;
    dfs(0, -1);
    calculate_dp(0);

    printf("%d\n", tot - dp[0].back());

    return 0;
}