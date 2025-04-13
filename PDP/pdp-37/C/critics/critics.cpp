#include <bits/stdc++.h>
#define pb push_back

#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

const int MAXLOG = 19;

int subtask;
int N;
vector<int> f;
vector<vector<int>> adj_list;

vector<int> prv, nxt;

vector<bool> in_cycle;
vector<int> outside;

vector<bool> visited;
vector<int> ans;

vector<int> heavyprv;
vector<int> heavynxt;

int optimal_outside;

bool dfs(int node, int par) {
    visited[node] = true;
    in_cycle[node] = false;

    bool cut = false;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        if (visited[neigh]) {
            if (in_cycle[neigh]) {
                // Found upper end of cycle
                cut = true;
            }
            else {
                // Found lower end of cycle
                in_cycle[node] = true;
                nxt[node] = neigh;
                prv[neigh] = node;
            }
        }
        else if (dfs(neigh, node)) {
            nxt[node] = neigh;
            prv[neigh] = node;
            in_cycle[node] = true;
        }
    }

    return in_cycle[node] && !cut;
}

void calculate_outside(int node, int par) {
    outside[node] = 0;
    int secondbest = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh == par || in_cycle[neigh]) {
            continue;
        }

        calculate_outside(neigh, node);
        if (outside[neigh] + 1 > outside[node]) {
            secondbest = outside[node];
            outside[node] = outside[neigh] + 1;
        }
        else if (outside[neigh] + 1 > secondbest) {
            secondbest = outside[neigh] + 1;
        }
    }

    optimal_outside = max(optimal_outside, outside[node] + secondbest);
}

int main(void) {
    scanf("%d", &subtask);

    scanf("%d", &N);
    
    f.resize(N);
    ans.assign(N, -1);
    adj_list.resize(N);
    visited.assign(N, false);
    in_cycle.assign(N, false);
    outside.resize(N);
    nxt.resize(N);
    prv.resize(N);

    optimal_outside = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &f[i]);
        f[i]--;

        adj_list[f[i]].pb(i);
        adj_list[i].pb(f[i]);
    }

    // dfs to find the cycle
    dfs(0, -1);

    // Find best node in cycle
    int heavy = -1;
    int cyclesize = 0;
    for (int i = 0; i < N; i++) {
        if (in_cycle[i]) {
            cyclesize++;
            calculate_outside(i, -1);
            if (heavy == -1 || outside[i] > outside[heavy]) {
                heavy = i;
            }
        }
    }

    if (f[heavy] != nxt[heavy]) {
        swap(prv, nxt);
    }

    // Find the best previous and next for heavy (for all i in [0..cyclesize))
    heavyprv.resize(cyclesize);
    heavynxt.resize(cyclesize);
    heavyprv[0] = heavynxt[0] = 0;

    int p = heavy, n = heavy;
    for (int d = 1; d < cyclesize; d++) {
        p = prv[p];
        n = nxt[n];

        heavyprv[d] = max(heavyprv[d - 1], d + outside[p]);
        heavynxt[d] = max(heavynxt[d - 1], d + outside[n]);
    }

    // Find the answers to all edges
    // Begin from heavy
    int node = heavy;
    for (int d = 0; d < cyclesize; d++) {
        ans[node] = max(ans[node], heavyprv[cyclesize - d - 1] + heavynxt[d]);
        ans[node] = max(ans[node], outside[heavy] + max(heavyprv[cyclesize - d - 1], heavynxt[d]));

        node = nxt[node];
    }

    for (int i = 0; i < N; i++) {
        if (ans[i] == -1) {
            printf("-1\n");
        }
        else {
            // Count nodes not edges
            ans[i] = max(ans[i], optimal_outside);
            printf("%d\n", ans[i] + 1);
        }
    }

    return 0;
}