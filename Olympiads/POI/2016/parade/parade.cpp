#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int n;
vector<vector<int>> adj_list;
int ans = 0;
// The maximum number of segments that should be closed such that the parade passes from i
vector<int> dp;

void calc_dp(int node, int par)
{
    // What if the parade starts at our current node
    dp[node] = adj_list[node].size() - 1;

    int b1 = 0, b2 = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            calc_dp(neigh, node);
            dp[node] = max(dp[node], (int)(dp[neigh] + adj_list[node].size() - 2));
            if (dp[neigh] >= b1) {
                b2 = b1;
                b1 = dp[neigh];
            }
            else if (dp[neigh] > b2)
                b2 = dp[neigh];
        }
    }

    ans = max(ans, b1 + b2 + (int)adj_list[node].size() - 2);
    ans = max(ans, b1 + (int)adj_list[node].size() - 1);
}

int main(void)
{
    scanf("%d", &n);
    dp.resize(n);
    adj_list.resize(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    calc_dp(0, -1);
    printf("%d\n", ans);

    return 0;
}