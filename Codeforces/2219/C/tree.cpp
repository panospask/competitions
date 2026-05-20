#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

int N;
vector<vector<int>> adj_list;

// Best if we use and don't use father
vector<vector<ld>> dp;

vector<int> S;

// How much can we gain by using part of cost
ld calculate(int s, vector<ld>& cost, int total) {
    ld totalcost = 0;
    int used = 0;
    for (int i = 0; i < cost.size(); i++) {
        ld prv = (s + i) ? (ld)total / (s + i) : 1e9;
        ld cur = (ld)total / (s + i + 1);

        if (cost[i] > prv - cur) {
            break;
        }
        totalcost += cost[i];
        used++;
    }

    if (used + s == 0) {
        return 1e9;
    }
    return (ld)(total) / (used + s) + totalcost;
}

void dfs(int node, int par) {
    vector<ld> cost;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);

        // How much does it cost to not use father
        cost.push_back(dp[neigh][0] - dp[neigh][1]);

        // Assume we use father
        dp[node][0] += dp[neigh][1];
        dp[node][1] += dp[neigh][1];
    }

    if (S[node]) {
        return;
    }

    sort(cost.begin(), cost.end());

    // Save by using some parts
    dp[node][0] += calculate(0, cost, adj_list[node].size());
    dp[node][1] += calculate(1, cost, adj_list[node].size());
}

void solve(void) {
    scanf("%d", &N);

    adj_list.assign(N, vector<int>());
    dp.assign(N, vector<ld>(2, 0));
    S.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%1d", &S[i]);
    }

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(0, -1);

    printf("%.6Lf\n", dp[0][0]);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}