#include <bits/stdc++.h>

using namespace std;

const int INF = 1e6;

int N, K;
vector<vector<int>> adj_list;
vector<int> dep;

// dp[node][s][f]: We are at node, can player s win? The value f denotes if there is a flip in the end states
vector<vector<vector<int>>> dp;

// lose[i][s][f]: What is the minimum distance from i to a node in the subtree of i s.t. s loses while moving first
vector<vector<vector<int>>> lose;

vector<int> ans;

void dfs(int node, int par) {
    if (adj_list[node].size() == 1) {
        for (int s = 0; s < 2; s++) {
            for (int f = 0; f < 2; f++) {
                // When f = 0, player 0 wins at even depth, and player 1 at odd depth. f just flips this
                dp[node][s][f] = (dep[node] % 2 == 0) ^ s ^ f;
            }
        }

        return;
    }

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }
        dep[neigh] = dep[node] + 1;
        dfs(neigh, node);

        for (int s = 0; s < 2; s++) {
            for (int f = 0; f < 2; f++) {
                lose[node][s][f] = min(lose[node][s][f], lose[neigh][s][f] + 1);
            }
        }
    }

    for (int s = 0; s < 2; s++) {
        for (int f = 0; f < 2 ; f++) {
            if (K >= lose[node][!s][f]) {
                // We have found a reachable state where !s loses
                dp[node][s][f] = true;
            }
            else {
                dp[node][s][f] = false;
            }
        }
    }

    for (int s = 0; s < 2; s++) {
        for (int f = 0; f < 2; f++) {
            if (dp[node][s][f] == false) {
                lose[node][s][f] = 0;
            }
        }
    }
}

void update(int& a, int& b, int c) {
    if (c < a) {
        swap(a, c);
    }
    if (c < b) {
        swap(b, c);
    }
}

// pass[s][f]: Values of lose for parent, to be treated as an extra child
void reroot(int node, int par, vector<vector<int>> pass) {
    // Targets for kids will be flipped iff dep[node] % 2 == 1
    bool flipkids = dep[node] % 2 == 1;

    // Reset everything. Calculate new losing stuff based on the current node being the root
    vector<vector<int>> firstlose(2, vector<int>(2, INF));
    // Keep the second biggest value as well
    vector<vector<int>> seclose(2, vector<int>(2, INF));

    for (int s = 0; s < 2; s++) {
        for (int f = 0; f < 2; f++) {
            update(firstlose[s][f], seclose[s][f], pass[s][f] + 1);
        }
    }

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        for (int s = 0; s < 2; s++) {
            for (int f = 0; f < 2; f++) {
                update(firstlose[s][f], seclose[s][f], lose[neigh][s][f ^ flipkids] + 1);
            }
        }
    }

    ans[node] = firstlose[0][0] <= K;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        vector<vector<int>> curlose(2, vector<int>(2, INF));
        for (int s = 0; s < 2; s++) {
            for (int f = 0; f < 2; f++) {
                if (firstlose[s][f] == lose[neigh][s][f ^ flipkids] + 1) {
                    curlose[s][f] = seclose[s][f];
                }
                else {
                    curlose[s][f] = firstlose[s][f];
                }
            }

        }
        // If we lose now, we could update curlose
        for (int s = 0; s < 2; s++) {
            for (int f = 0; f < 2; f++) {
                if (curlose[!s][f] > K) {
                    curlose[s][f] = 0;
                }
            }
        }

        reroot(neigh, node, curlose);
    }
}

void solve(void) {
    int N;
    scanf("%d %d", &N, &K);

    adj_list.assign(N, vector<int>());
    lose.assign(N, vector<vector<int>>(2, vector<int>(2, INF)));
    dp.assign(N, vector<vector<int>>(2, vector<int>(2, false)));

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    ans.resize(N);
    dep.resize(N);
    dep[0] = 0;
    dfs(0, -1);

    vector<vector<int>> inp(2, vector<int>(2, INF));
    reroot(0, -1, inp);

    for (int i = 0; i < N; i++) {
        printf("%d ", ans[i]); 
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}