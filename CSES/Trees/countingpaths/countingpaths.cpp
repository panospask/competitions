#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << pos))
#define pb push_back

using namespace std;

const int MAXANC = 20;
const int ROOT = 0;

int N, M;
vector<vector<int>> adj_list;
vector<vector<int>> ancestor;
vector<int> dep;
vector<int> cnt;
vector<int> ans;

void init_dfs(int node, int par)
{
    ancestor[0][node] = par;
    dep[node] = (par != -1 ? dep[par] + 1 : 0);

    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            init_dfs(neigh, node);
        }
    }
}

void precalc_ancestors(void)
{
    for (int up = 1; up < MAXANC; up++) {
        for (int i = 0; i < N; i++) {
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
        }
    }
}

int jump(int a, int b)
{
    for (int up = 0; up < MAXANC; up++) {
        if (CHECK_BIT(b, up)) {
            a = ancestor[up][a];
        }
    }

    return a;
}

int lca(int a, int b)
{
    if (dep[a] < dep[b]) {
        swap(a, b);
    }

    a = jump(a, dep[a] - dep[b]);
    if (a == b) {
        return a;
    }

    for (int up = MAXANC - 1; up >= 0; up--) {
        int n_a = ancestor[up][a];
        int n_b = ancestor[up][b];

        if (n_a != n_b) {
            a = n_a;
            b = n_b;
        }
    }

    return ancestor[0][a];
}

int final_dfs(int node)
{
    int s = cnt[node];
    for (auto neigh : adj_list[node]) {
        if (neigh != ancestor[0][node]) {
            s += final_dfs(neigh);
        }
    }

    return ans[node] = s;
}

int main(void)
{
    scanf("%d %d", &N, &M);

    adj_list.resize(N);
    ans.resize(N);
    ancestor.resize(MAXANC, vector<int>(N));
    dep.assign(N, 0);
    cnt.assign(N, 0);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    // Initialize LCA binary lifting
    ancestor[ROOT][0] = ROOT;
    init_dfs(ROOT, ROOT);
    precalc_ancestors();

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        int l = lca(u, v);
        cnt[u]++;
        cnt[v]++;

        // Merge the two paths
        cnt[l]--;
        if (ancestor[0][l] != l) {
            // Finish the path
            cnt[ancestor[0][l]]--;
        }
    }

    final_dfs(ROOT);

    for (int i = 0; i < N; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}