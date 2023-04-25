#include <bits/stdc++.h>
#define pb push_back
#define CHECK_BIT(val, pos) (val & (1<<pos))

using namespace std;

typedef pair<int, int> ii;

int n, k;
vector<vector<int>> adj_list;
vector<vector<int>> trimlist;
vector<int> subheight;
vector<int> p;
vector<int> depth;
vector<int> trimnum;
vector<ii> leafs;
int leafsize;
vector<vector<int>> depthnodes;
int trimcount = 0;
vector<int> dp;
int tot_leafs = 0;

void dfs(int node, int par, int d)
{
    depth[node] = subheight[node] = d;
    if (depth[node] == k) {
        leafs[node].first = leafs[node].second = ++tot_leafs;
        depthnodes[d].pb(node);
        return;
    }
    for (auto kid : adj_list[node])
        if (kid != par) {
            dfs(kid, node, d + 1);
            subheight[node] = max(subheight[node], subheight[kid]);
            leafs[node].first = min(leafs[node].first, leafs[kid].first);
            leafs[node].second = max(leafs[node].second, leafs[kid].second);
        }

    if (subheight[node] == k)
        depthnodes[d].push_back(node);
}

int main(void)
{
    scanf("%d %d", &n, &k);
    if (k * k > n) {
        printf("DA\n");
        return 0;
    }

    adj_list.resize(n);
    subheight.resize(n);
    depth.resize(n);
    leafs.assign(n, make_pair(INT_MAX, INT_MIN));
    depthnodes.resize(k+1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    dfs(0, -1, 0);

    dp.resize(1<<k);
    dp[0] = 0;
    for (int s = 0; s < (1<<k); s++) {
        if (dp[s] == tot_leafs) {
            printf("DA\n");
            return 0;
        }
        for (int d = 0; d < k; d++)
            if (!CHECK_BIT(s, d)) {
                int prv_max = dp[s];
                for (auto node : depthnodes[d+1]) {
                    if (leafs[node].first <= prv_max + 1)
                        dp[s | (1<<d)] = max(dp[s | (1<<d)], leafs[node].second);
                }
            }
    }


    printf("NE\n");
    return 0;
}