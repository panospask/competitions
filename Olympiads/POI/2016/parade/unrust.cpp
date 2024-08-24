#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<vector<int>> adj_list;

int ans = 0;

int dfs(int node, int par)
{
    int op1 = 0, op2 = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        int res = dfs(neigh, node);

        if (op2 < res) {
            op2 = res;
            if (op1 < op2) {
                swap(op1, op2);
            }
        }
    }

    ans = max(ans, (int)adj_list[node].size() - 1 + op1 + max(op2 - 1, 0));

    return adj_list[node].size() - 1 + max(op1 - 1, 0);
}

int main(void)
{
    scanf("%d", &N);

    adj_list.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    dfs(0, 0);

    printf("%d\n", ans);

    return 0;
}