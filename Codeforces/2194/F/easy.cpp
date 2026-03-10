#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int MOD = 1e9 + 7;

int N, K;
vector<int> A;
vector<int> B;
vector<vector<int>> adj_list;
vector<vector<int>> dp;
vector<int> v;
vector<int> subtree;

int ans = 0;

void merge(vector<int>& a, vector<int>& b) {
    vector<int> c = a;
    for (int mask = 0; mask < (1 << K); mask++) {
        for (int m1 = 0; m1 < (1 << K); m1++) {
            c[mask] = ((long long)(a[m1]) * b[mask ^ m1]) % MOD;
        }
    }

    swap(a, c);
}

void dfs(int node, int par) {
    subtree[node] = A[node];
    dp[node][0] = 1;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        subtree[node] ^= subtree[neigh];
        merge(dp[node], dp[neigh]);
    }

    vector<int> dp2 = dp[node];
    for (int mask = 0; mask < (1 << K); mask++) {
        for (int i = 0; i < K; i++) {
            if (v[mask] ^ subtree[node] == B[i]) {
                dp2[subtree[node]] = (dp[node][subtree[node]] + dp[node][mask]) % MOD;
                if (node == 0) {
                    ans = (ans + dp[node][mask]) % MOD;
                }
            }
        }
    }
}

void solve(void) {
    scanf("%d %d", &N, &K);

    A.resize(N);
    subtree.resize(N);
    B.resize(K);
    dp.assign(N, vector<int>(1 << K, 0));
    adj_list.assign(N, vector<int>());
    ans = 0;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < K; i++) {
        scanf("%d", &B[i]);
    }

    dfs(0, -1);

    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}