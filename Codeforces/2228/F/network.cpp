#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, K;
vector<vector<int>> adj_list;
vector<int> a;
vector<ll> subtree;

// dp[node][i]: What is the path that has i edges, ends at node, and has the maximum min compo weight
vector<deque<ll>> dp;

void dfs(int node, int par) {
    subtree[node] = a[node];

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }
        dfs(neigh, node);
        subtree[node] += subtree[neigh];
    }

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }
        
    }
}

void solve(void) {
    ;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}