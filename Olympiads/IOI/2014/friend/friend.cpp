#include <bits/stdc++.h>
#include "friend.h"
#define pb push_back

using namespace std;

typedef long long ll;

int N;
vector<int> a;
vector<int> op;
vector<vector<int>> kids;

/* dp[i][able]:
 * Maximum total confidence in the subtree of i
 * 
 * taken is a boolean variable denoting if we have taken a node that 
 * has connections to the remaining friends of i
 */
vector<vector<int>> dp;

void dfs(int node)
{
    dp[node][true] = a[node];
    dp[node][false] = 0;

    for (auto kid : kids[node]) {
        dfs(kid);

        if (op[kid] == 0) {
            // This kid has connection only to outside of its subtree

            dp[node][false] = dp[node][false] + max(dp[kid][false], dp[kid][true]);

            dp[node][true] = dp[node][true] + dp[kid][false];
        }
        else if (op[kid] == 1) {
            // This kid has connections to all friends of node that will be processed after it

            // We can take both the kid and the node as they don't have a connection
            // However we would need to eliminate all further connections to node by taking either

            dp[node][true] = max(dp[node][true] + max(dp[kid][false], dp[kid][true]), max(dp[node][false], dp[node][true]) + dp[kid][true]);
            dp[node][false] = dp[node][false] + dp[kid][false];
        }
        else {
            // This kid has both of the above types of edges

            // Taking either node or kid eliminates furher connections and we cannot take both

            dp[node][true] = max(dp[node][true] + dp[kid][false], dp[node][false] + dp[kid][true]);
            dp[node][false] = dp[node][false] + dp[kid][false];
        }
    }
}

int findSample(int n,int confidence[],int host[],int protocol[])
{
    N = n;

    a.resize(N);
    op.resize(N);   
    kids.resize(N);
    dp.resize(N, vector<int>(2, 0));

    a[0] = confidence[0];
    for (int i = 1; i < N; i++) {
        kids[host[i]].pb(i);
        op[i]= protocol[i];
        a[i] = confidence[i];
    }

    for (int i = 0; i < N; i++) {
        reverse(kids[i].begin(), kids[i].end());
    }

    dfs(0);
    
    return max(dp[0][0], dp[0][1]);
}