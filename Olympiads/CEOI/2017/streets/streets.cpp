#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int MAXUP = 20;

int N, M, P;
vector<vector<int>> adj_list;
vector<pi> edges;
vector<bool> visited;

/* dp[node]:
 * Number of back edges between node and par[node]
 */
vector<int> dp;

vector<vector<int>> ancestor;
vector<int> dep;

vector<int> upwards, downwards;

void dfs(int node, int par)
{
    ancestor[0][node] = par;
    dp[node] = 0;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            par = -1;
            continue;
        }
        else if (dep[neigh] == -1) {
            dep[neigh] = dep[node] + 1;
            dfs(neigh, node);
            dp[node] += dp[neigh];
        }
        else {
            // This is a back edge
            if (dep[neigh] < dep[node]) {
                dp[node]++;
            }
            else if (dep[neigh] > dep[node]) {
                dp[node]--;
            }
        }
    }
}

void propagate(int node, int par)
{
    visited[node] = true;

    for (auto neigh : adj_list[node]) {
        if (dep[neigh] == dep[node] + 1 && !visited[neigh]) {
            propagate(neigh, node);
            upwards[node] += upwards[neigh];
            downwards[node] += downwards[neigh];
        }
    }
}

int jump(int a, int v)
{
    for (int up = 0; up < MAXUP; up++) {
        if (v & (1 << up)) {
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

    for (int up = MAXUP - 1; up >= 0; up--) {
        int n_a = ancestor[up][a];
        int n_b = ancestor[up][b];

        if (n_a != n_b) {
            a = n_a;
            b = n_b;
        }
    }

    return ancestor[0][a];
}

void precalculate(void)
{
    for (int up = 1; up < MAXUP; up++) {
        for (int i = 0; i < N; i++) {
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
        }
    }
}

int main(void)
{
    scanf("%d %d", &N, &M);

    adj_list.resize(N);
    ancestor.resize(MAXUP, vector<int>(N));
    dep.assign(N, -1);
    upwards.assign(N, 0);
    downwards.assign(N, 0);
    dp.resize(N);
    visited.assign(N, false);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
        edges.pb(mp(u, v));
    }

    for (int i = 0; i < N; i++) {
        if (dep[i] == -1) {
            dep[i] = 0;
            dfs(i, i);
        }
    }
    precalculate();

    scanf("%d", &P);
    for (int i = 0; i < P; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        int l = lca(u, v);

        upwards[u]++;
        downwards[v]++;
        upwards[l]--;
        downwards[l]--;
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i])
            propagate(i, i);
    }

    for (auto [u, v] : edges) {
        int swaped = 0;
        if (dep[u] > dep[v]) {
            swap(u, v);
            swaped = 1;
        }


        if (dep[v] != dep[u] + 1 || dp[v] != 0) {
            printf("B");
        }
        else {
            if (upwards[v] == 0 && downwards[v] == 0) {
                printf("B");
            }
            else {
                assert(upwards[v] == 0 || downwards[v] == 0);
                if ((upwards[v] != 0) ^ swaped) { 
                    printf("L");
                }
                else {
                    printf("R");
                }
            }
        }
    }
    printf("\n");
}