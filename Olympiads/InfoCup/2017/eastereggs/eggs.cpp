#include <bits/stdc++.h>
#include "grader.h"

#define pb push_back

using namespace std;

vector<vector<int>> adj_list;

vector<int> dfs_order;

void dfs(int node, int par)
{
    dfs_order.pb(node + 1);

    for (auto neigh : adj_list[node])
        if (neigh != par)
            dfs(neigh, node);
}

int findEgg(int N, vector<pair<int, int>> bridges)
{
    adj_list.clear();
    dfs_order.clear();

    adj_list.resize(N);

    for (int i = 0; i < N - 1; i++) {
        adj_list[bridges[i].first - 1].pb(bridges[i].second - 1);
        adj_list[bridges[i].second - 1].pb(bridges[i].first - 1);
    }

    dfs(0, -1);

    int l = -1;
    int r = N - 1;

    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (query(vector<int>(dfs_order.begin(), dfs_order.begin() + mid + 1)))
            r = mid;
        else
            l = mid;
    }

    return dfs_order[r];
}
