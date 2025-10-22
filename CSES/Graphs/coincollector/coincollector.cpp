#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

// Kosajaru's algo
// Natural toposort order is 0, ..., groups-1

int N, M;
vector<vector<int>> adj_list;
vector<vector<int>> revlist;

// Number of groups
int groups = 0;

// idx[i]: Which group does i belong to in the resulting dag
vector<int> idx;

// connections in the resulting dag
vector<vector<int>> connections;

// Auxilary
vector<bool> visited;
stack<int> s;

void dfs1(int node) {
    if (visited[node]) {
        return;
    }

    visited[node] = true;
    
    // Ensure everything reachable by node goes before it in the stack
    for (auto neigh : adj_list[node]) {
        dfs1(neigh);
    }

    s.push(node);
}

void dfs2(int node) {
    for (auto neigh : revlist[node]) {
        if (idx[neigh] == -1) {
            idx[neigh] = idx[node];
            dfs2(neigh);
        }
        else {
            connections[idx[neigh]].pb(idx[node]);
        }
    }
}

void kosaraju(void) {
    connections.clear();
    revlist.assign(N, vector<int>());
    for (int i = 0; i < N; i++) {
        for (auto v : adj_list[i]) {
            revlist[v].pb(i);
        }
    }

    visited.assign(N, false);
    for (int i = 0; i < N; i++) {
        dfs1(i);
    }

    groups = 0;
    idx.assign(N, -1);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (idx[node] != -1) {
            continue;
        }
        idx[node] = groups;
        connections.pb(vector<int>());
        dfs2(node);
        groups++;
    }

    // Remove duplicates (not required)
    for (int g = 0; g < groups; g++) {
        sort(connections[g].begin(), connections[g].end());
        connections[g].resize(unique(connections[g].begin(), connections[g].end()) - connections[g].begin());
    }
}

vector<int> K;
vector<ll> groupsum;
vector<ll> dp;

int main(void) {
    scanf("%d %d", &N, &M);
    
    adj_list.assign(N, vector<int>());
    K.resize(N);
    dp.resize(N);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &K[i]);
    }
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
    }
    
    kosaraju();
    groupsum.resize(groups);

    for (int i = 0; i < N; i++) {
        groupsum[idx[i]] += K[i];
    }

    ll ans = 0;
    for (int g = 0; g < groups; g++) {
        dp[g] += groupsum[g];
        ans = max(ans, dp[g]);

        for (auto h : connections[g]) {
            dp[h] = max(dp[h], dp[g]);
        }
    }

    printf("%lld\n", ans);

    return 0;
}

