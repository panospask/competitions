#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, K;
vector<vector<int>> adj_list;
vector<int> S;

vector<vector<int>> cities;
vector<ll> v;
vector<ll> subtree;

int ans = 0;

int dfs(int node, int par) {
    subtree[node] = v[node];

    int res = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        res += dfs(neigh, node);
        subtree[node] ^= subtree[neigh];
    }

    if (subtree[node] == 0) {
        if (res == 0) {
            // This is a "leaf" node
            ans++;
        }
        else if (res == 1 && par == -1) {
            ans++;
        }
        res = 1;
    }

    return res;
}

int main(void) {
    scanf("%d %d", &N, &K);

    adj_list.resize(N);
    S.resize(N);
    v.resize(N);
    subtree.resize(N);
    cities.resize(K);

    mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
    
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
        S[i]--;
        cities[S[i]].push_back(i);
    }

    for (int i = 0; i < K; i++) {
        ll cur = 0;
        for (int j = 0; j < cities[i].size() - 1; j++) {
            v[cities[i][j]] = uniform_int_distribution<ll>(0, LLONG_MAX)(rng);
            cur ^= v[cities[i][j]];
        }
        v[cities[i].back()] = cur;
    }

    dfs(0, -1);

    if (ans == 1) {
        printf("0\n");
        return 0;
    }
    
    printf("%d\n", (ans + 1) / 2);
}