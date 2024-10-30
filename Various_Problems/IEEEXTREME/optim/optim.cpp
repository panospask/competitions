#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 99999;

int N;
vector<int> subtree;
vector<ll> w;
vector<vector<int>> adj_list;

vector<vector<ll>> choose;
vector<ll> modify;

vector<ll> ans;

void precalc(void)
{
    choose.assign(N + 1, vector<ll>(N + 1, 0));

    for (int i = 0; i <= N; i++) {
        choose[i][0] = choose[i][i] = 1;
        for (int j = 1; j < i; j++) {
            choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % MOD;
        }
    }
}

void add(ll& a, ll b)
{
    a = a + b;
    a %= MOD;
}

void dfs(int node, int par)
{
    subtree[node] = 1;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        subtree[node] += subtree[neigh];

        add(modify[subtree[neigh]], w[node]);
    }

    add(modify[N - subtree[node]], w[node]);
}

int main(void)
{
    scanf("%d", &N);

    precalc();

    adj_list.resize(N);
    ans.resize(N + 1);
    subtree.resize(N + 1);
    modify.assign(N + 1, 0);
    w.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%lld", &w[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    for (int l = 1; l <= N; l++) {
        for (int i = 0; i < N; i++) {
            add(ans[l], w[i] * choose[N][l] % MOD);
        }
    }

    subtree.resize(N);
    dfs(0, -1);

    for (int l = 1; l <= N; l++) {
        for (int i = 1; i <= l; i++) {
            add(ans[i], (MOD-modify[l]) * choose[l][i] % MOD);
        }
    }

    for (int l = 1; l <= N; l++) {
        ans[l] = (ans[l] % MOD + MOD) % MOD;
        printf("%lld\n", ans[l]);
    }

    return 0;
}