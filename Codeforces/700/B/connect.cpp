#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, K;
vector<vector<int>> adj_list;
vector<bool> uni;
vector<int> subtree_size;
vector<int> dep;

void dfs(int node, int par)
{
    dep[node] = (par != node ? dep[par] + 1 : 0);
    subtree_size[node] = uni[node];

    for (auto kid : adj_list[node]) {
        if (kid != par) {
            dfs(kid, node);
            subtree_size[node] += subtree_size[kid];
        }
    }
}

int find_center(int node, int par)
{
    for (auto kid : adj_list[node]) {
        if (kid != par && subtree_size[kid] > K) {
            return find_center(kid, node);
        }
    }

    return node;
}

int main(void)
{
    scanf("%d %d", &N, &K);

    uni.assign(N, false);
    adj_list.resize(N);
    dep.resize(N);
    subtree_size.resize(N);

    for (int i = 0; i < 2 * K; i++) {
        int u;
        scanf("%d", &u);

        uni[u - 1] = true;
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(0, 0);
    int c = find_center(0, 0);
    dfs(c, c);

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        if (uni[i]) {
            ans += dep[i];
        }
    }

    printf("%lld\n", ans);

    return 0;
}