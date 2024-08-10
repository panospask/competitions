#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define CHECK_BIT(var, pos) ((var) & (1 << pos))

using namespace std;

typedef pair<int, int> pi;

const int MAXANC = 18;

int N, Q;
vector<vector<int>> adj_list;
vector<int> dep;

vector<pi> secdist;
vector<pi> maxdist;

vector<vector<int>> ancestor;

void upd_dist(int i, pi d)
{
    if (maxdist[i] < d) {
        secdist[i] = maxdist[i];
        maxdist[i] = d;
    }
    else if (secdist[i] < d) {
        secdist[i] = d;
    }
}

void dfs(int node, int par)
{
    ancestor[0][node] = par;
    maxdist[node] = mp(0, node);

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dep[neigh] = dep[node] + 1;
        dfs(neigh, node);
        upd_dist(node, mp(maxdist[neigh].first + 1, maxdist[neigh].second));
    }
}

void propagate_children(int node, int par)
{
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        if (maxdist[neigh].second != maxdist[node].second) {
            upd_dist(neigh, mp(maxdist[node].first + 1, maxdist[node].second));
        }
        else {
            upd_dist(neigh, mp(secdist[node].first + 1, secdist[node].second));
        }
        propagate_children(neigh, node);
    }
}

void compute_ancestors(void)
{
    for (int up = 1; up < MAXANC; up++) {
        for (int i = 0; i < N; i++) {
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
        }
    }
}

int jump(int node, int v)
{
    for (int up = 0; up < MAXANC; up++) {
        if (CHECK_BIT(v, up)) {
            node = ancestor[up][node];
        }
    }

    return node;
}

int main(void)
{
    scanf("%d", &N);

    adj_list.resize(N);
    ancestor.resize(MAXANC, vector<int>(N));
    dep.resize(N);
    maxdist.resize(N);
    secdist.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    dfs(0, 0);
    propagate_children(0, 0);

    compute_ancestors();

    scanf("%d", &Q);

    while (Q--) {
        int u, d;
        scanf("%d %d", &u, &d);
        u--;

        if (d > maxdist[u].first) {
            printf("-1\n");
            continue;
        }
        
        int node;
        if (d <= dep[u]) {
            node = jump(u, d);
        }
        else {
            node = jump(maxdist[u].second, maxdist[u].first - d);
        }
        printf("%d\n", node + 1);
    }
}