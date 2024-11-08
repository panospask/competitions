#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<vector<int>> adj_list;

// losekids[node]: How many of this nodes kids are losing if you move from this node to there?
vector<int> losekids;

// Does planting the chip in this node result in a winning or losing state?
vector<bool> state;

bool loses(int node)
{
    return losekids[node] == 0;
}

void dfs(int node, int par)
{
    losekids[node] = 0;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        losekids[node] += loses(neigh);
    }
}

void reroot(int node, int par, bool lose_par)
{
    state[node] = losekids[node] + lose_par > 0;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        reroot(neigh, node, !(losekids[node] + lose_par - loses(neigh) > 0));
    }
}

int main(void)
{
    scanf("%d", &N);

    adj_list.resize(N);
    state.resize(N);    
    losekids.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    dfs(0, -1);
    reroot(0, -1, 0);

    int bad = 0;
    for (int i = 0; i < N; i++) {
        bad += !state[i];
    }

    if (bad) {
        printf("Alice\n");
    }
    else {
        printf("Bob\n");
    }
}