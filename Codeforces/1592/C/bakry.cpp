#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<vector<int>> adj_list;
vector<int> A;
vector<int> subtree;
int sum = 0;

int dfs(int node, int par) {
    subtree[node] = A[node];;

    int cnt = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        cnt += dfs(neigh, node);
        subtree[node] ^= subtree[neigh];
    }

    if ((subtree[node] ^ ((cnt % 2) * sum)) == sum) {
        cnt++;
    }

    return cnt;
}

void solve(void) {
    scanf("%d %d", &N, &K);

    adj_list.assign(N, vector<int>());
    A.resize(N);
    subtree.resize(N);
    sum = 0;
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        sum = sum ^ A[i];
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    if (sum == 0) {
        printf("YES\n");
        return;
    }
    if (K == 2) {
        printf("NO\n");
        return;
    }

    int ans = dfs(0, -1);

    if (ans >= 3) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}