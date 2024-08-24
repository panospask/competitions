#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const int DEFAULT = -1;
const int DEAD = 1e9 + 1;

const int MOD = 1e9 + 7;

int target = 0;
int ans = DEFAULT;

int N, M;
vector<vector<int>> adj_list;
vector<int> dep;
vector<int> state;
vector<int> cycles;

bool allgood = true;
ll tot = 0;

void dfs(int node, int par)
{
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        if (dep[neigh] == DEFAULT) {
            dep[neigh] = dep[node] + 1;
            dfs(neigh, node);
        }
        else if (dep[neigh] < dep[node]) {
            // Cycle
            int len = dep[node] - dep[neigh] + 1;

            if (ans == len || ans == DEFAULT) {
                ans = len;
            }
            else {
                ans = N + 1;
            }
        }
    }
}

void update(int node, int s)
{
    if (s == DEAD || state[node] == DEAD) {
        state[node] = DEAD;
        allgood = false;
        return;
    }
    if (s == DEFAULT) {
        // No cycle here
        return;
    }
    if (state[node] == DEFAULT) {
        state[node] = s;
        cycles[node]++;
        return;
    }
    if (s >= N || state[node] >= N) {
        allgood = false;
        state[node] = DEAD;
        return;
    }

    if (s != dep[node] && state[node] != dep[node]) {
        state[node] = DEAD;
        allgood = false;
        return;
    }

    tot = (tot + (ll)cycles[node]) % MOD;
    cycles[node]++;
    state[node] = min(state[node], s);
}

int find_cycles(int node, int par)
{
    cycles[node] = 0;
    bool have = false;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        if (dep[neigh] < dep[node]) {
            tot++;
            update(node, (target == DEAD ? N + dep[node] - ans + 2 : dep[node] - target));
        }
    }


    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        if (dep[neigh] == dep[node] + 1) {
            update(node, find_cycles(neigh, node));
        }
    }

    if (state[node] == N + dep[node]) {
        state[node] = DEFAULT;
    }
    else if (state[node] == dep[node]) {
        state[node] = N + dep[node] - target;
    }
    else if (state[node] != DEAD && cycles[node] >= 2) {
        state[node] = N + dep[node] - target;
        for (auto neigh : adj_list[node]) {
            if (neigh == par) {
                continue;
            }

            if (dep[neigh] == dep[node] + 1 && state[neigh] != DEFAULT) {
                state[node] = min(state[node], N + state[neigh] - target);
            }
        }
    }

    return state[node];
}

int main(void)
{
    scanf("%d %d", &N, &M);

    adj_list.resize(N);
    dep.assign(N, DEFAULT);
    state.assign(N, DEFAULT);
    cycles.assign(N, 0);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        
        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    ans = DEFAULT;
    tot = 0;
    dep[0] = 0;
    dfs(0, 0);

    if (ans == DEFAULT) {
        printf("BRAK\n");
        return 0;
    }
    else if (ans == N + 1) {
        printf("NIE\n");
        return 0;
    }

    if (ans % 2 == 0) {
        target = ans / 2 - 1;
    }
    else {
        target = DEAD;
    }
    tot = 0;
    find_cycles(0, 0);

    tot %= MOD;

    // Choose any starting vertex and any direction of travel
    tot = tot * ans * 2 % MOD;

    if (!allgood) {
        printf("NIE\n");
        return 0;
    }

    printf("TAK\n%d %lld\n", ans, tot);
}