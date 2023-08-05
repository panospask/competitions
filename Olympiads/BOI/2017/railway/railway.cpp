#include <bits/stdc++.h>
#define CHECK_BIT(val, pos) (val & (1 << pos))
#define pb push_back
#define mp make_pair

using namespace std;

const int MAXLOG = 17;

int N, M, K;

typedef pair<int, int> pi;

vector<vector<int>> adj_list;
vector<int> ancestor[MAXLOG];
vector<int> dep;
map<pi, int> edges;
vector<set<int>> active;
vector<bool> is_active;

vector<int> ans;

vector<vector<int>> starting;
vector<vector<int>> ending;

int jump(int v, int lvl)
{
    for (int up = 0; up < MAXLOG; up++)
        if (CHECK_BIT(lvl, up))
            v = ancestor[up][v];

    return v;
}

int lca(int a, int b)
{
    if (dep[a] < dep[b])
        swap(a, b);

    a = jump(a, dep[a] - dep[b]);

    if (a == b)
        return a;

    for (int up = MAXLOG - 1; up >= 0; up--) {
        int aa = ancestor[up][a];
        int ab = ancestor[up][b];

        if (aa != ab) {
            a = aa;
            b = ab;
        }
    }

    return ancestor[0][a];
}

void dfs(int node, int d)
{
    dep[node] = d;

    for (auto neigh : adj_list[node]) {
        if (neigh != ancestor[0][node]) {
            ancestor[0][neigh] = node;
            dfs(neigh, d + 1);
        }
    }
}

void calculate_ancestors(void)
{
    for (int up = 1; up < MAXLOG; up++) {
        ancestor[up].resize(N + 1);
        for (int i = 0; i < N; i++)
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
    }
}

// Check if the road connecting this node to the parent is necessary
void calculate_necessity(int node)
{
    for (auto neigh : adj_list[node])
        if (neigh != ancestor[0][node]) {
            calculate_necessity(neigh);
            if (active[neigh].size() > active[node].size())
                swap(active[neigh], active[node]);

            for (auto v : active[neigh])
                active[node].insert(v);
        }

    for (auto r : starting[node])
        active[node].insert(r);
    for (auto r : ending[node])
        active[node].erase(r);

    if (active[node].size() >= K)
        ans.pb(edges[mp(node, ancestor[0][node])]);

    return;
}

int main(void)
{
    scanf("%d %d %d", &N, &M, &K);

    adj_list.resize(N);
    active.resize(N);
    ancestor[0].resize(N + 1);
    starting.resize(N);
    ending.resize(N);
    dep.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
        edges[mp(u, v)] = i;
        edges[mp(v, u)] = i;
    }

    ancestor[0][0] = N;
    ancestor[0][N] = N;
    dfs(0, 0);
    calculate_ancestors();

    for (int i = 0; i < M; i++) {
        int l;
        scanf("%d", &l);

        int anc;
        scanf("%d", &anc);
        anc--;
        starting[anc].pb(i);
        for (int j = 1; j < l; j++) {
            int v;
            scanf("%d", &v);
            v--;
            starting[v].pb(i);

            anc = lca(anc, v);
        }

        ending[anc].pb(i);
    }

    calculate_necessity(0);

    sort(ans.begin(), ans.end());

    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++)
        printf("%d ", ans[i] + 1);
    printf("\n");

    return 0;
}