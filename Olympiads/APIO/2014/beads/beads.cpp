#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e9;

int N;
vector<vector<pi>> adj_list;

/* dp[node][is_middle]:
 * The maximum score in the subtree of node.
 * is_middle is a boolean variable denoting if node was inserted in the middle via insert operation
 */
vector<vector<int>> dp;

int ans = 0;

void process_subtree(int node, int par)
{
    dp[node][0] = 0;
    dp[node][1] = -INF;
    
    // Maximum gain from using one of the kids as an endpoint for a red edge starting at par
    // and then inserting node and making the edges blue
    int opt_follow = -INF;

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        process_subtree(neigh, node);

        // Gain is the maximum we can get
        int gain = max(dp[neigh][1] + w, dp[neigh][0]);

        dp[node][0] += gain;

        opt_follow = max(opt_follow, dp[neigh][0] + w - gain);
    }

    if (opt_follow != -INF) {
        dp[node][1] = dp[node][0] + opt_follow;
    }
}

// reroot the tree at node
// par_dp is the dp of par if it acted as a kid of node
void reroot(int node, int par, vector<int>par_dp)
{
    int total = 0;

    // The 2 best children(1 may be the parent) to use as endpoints for a red edge to be deleted
    int opt1 = -INF, opt2 = -INF;

    for (auto [neigh, w] : adj_list[node]) {
        int gain;
        int cur_opt;
        if (neigh == par) {
            // Now par acts as a kid of current node
            gain = max(par_dp[1] + w, par_dp[0]);
            cur_opt = par_dp[0] + w - gain;
        }
        else {
            gain = max(dp[neigh][1] + w, dp[neigh][0]);
            cur_opt = dp[neigh][0] + w - gain;
        }

        total += gain;

        if (cur_opt > opt2) {
            opt2 = cur_opt;
            if (opt2 > opt1) {
                swap(opt2, opt1);
            }
        }
    }

    ans = max(ans, total);

    // Now process the kids
    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        int gain = max(dp[neigh][1] + w, dp[neigh][0]);
        int cur_opt = dp[neigh][0] + w - gain;

        total -= gain;
        
        int optimal = opt1;
        if (cur_opt == optimal) {
            optimal = opt2;
        }

        int tot_as_mid = -INF;
        if (optimal != -INF) {
            tot_as_mid = total + optimal;
        }

        reroot(neigh, node, {total, tot_as_mid});

        total += gain;
    }   
}

int main(void)
{
    scanf("%d", &N);

    adj_list.resize(N);
    dp.resize(N, vector<int>(2, -INF));

    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(mp(v, w));
        adj_list[v].pb(mp(u, w));
    }

    process_subtree(0, 0);
    reroot(0, 0, {0, -INF});

    printf("%d\n", ans);

    return 0;
}