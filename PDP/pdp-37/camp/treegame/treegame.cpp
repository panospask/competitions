#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int N, R, K, L;
ll ans = 0;

vector<vector<int>> adj_list;
vector<int> A;
vector<ll> subtree;
vector<int> cnt;

vector<int> dp1;
vector<int> dp2;

vector<ll> dp3;
vector<ll> dp4;

void dfs(int node, int par) {
    cnt[node] = 1;
    subtree[node] = A[node];

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        subtree[node] += subtree[neigh];
        cnt[node] += cnt[neigh];
    }

    return;
}

void calculate(int node, int par) {
    dp1[node] = dp2[node] = dp3[node] = dp4[node] = 0;

    if (cnt[node] <= K) {
        dp1[node] = cnt[node];
        dp3[node] = subtree[node];
        if (node != R) {
            ans = max(ans, subtree[node]);
        }
    }
    if (cnt[node] <= L) {
        dp2[node] = cnt[node];
        dp4[node] = subtree[node];
        if (node != R) {
            ans = max(ans, subtree[node]);
        }
    }
    dp3[node] = max(dp3[node], 0LL);
    dp4[node] = max(dp4[node], 0LL);

    ll opt3 = 0;
    ll opt4 = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        calculate(neigh, node);

        ans = max(ans, dp3[neigh] + opt4);
        ans = max(ans, dp4[neigh] + opt3);

        opt3 = max(opt3, dp3[neigh]);
        opt4 = max(opt4, dp4[neigh]);

        dp3[node] = max(dp3[node], dp3[neigh]);
        dp4[node] = max(dp4[node], dp4[neigh]);

        dp1[node] = max(dp1[node], dp1[neigh]);
        dp2[node] = max(dp2[node], dp2[neigh]);
    }
    
    // Find nested
    if (node != R) {
        if (dp1[node] + L >= cnt[node]) {
            ans = max(ans, subtree[node]);
        }
        if (dp2[node] + K >= cnt[node]) {
            ans = max(ans, subtree[node]);
        }
    }
}

int main(void) {
    scanf("%d %d %d %d", &N, &R, &K, &L);
    R--;

    A.resize(N);
    dp1.resize(N);
    dp2.resize(N);
    dp3.resize(N);
    dp4.resize(N);
    cnt.resize(N);
    subtree.resize(N);
    adj_list.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(R, -1);
    calculate(R, -1);

    printf("%lld\n", ans);
}