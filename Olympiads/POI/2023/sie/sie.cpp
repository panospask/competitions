#include <bits/stdc++.h>
#define pb push_back
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

const int INF = 1e6;

int N, M, K;

vector<vector<int>> new_list;
vector<vector<int>> adj_list;
vector<vector<int>> dist;
vector<int> ans;

vector<int> side;
vector<int> tot[2];
vector<int> match;
vector<bool> tried;

vector<bool> reachable;

void negative(void)
{
    printf("NIE\n");
    exit(0);
}

void assign_sides(int source)
{
    tot[0].clear();
    tot[1].clear();

    queue<int> q;
    q.push(source);
    side[source] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        tot[side[u]].pb(u);

        for (auto v : adj_list[u]) {
            if (side[v] != -1) {
                if (side[u] == side[v]) {
                    negative();
                }
            }
            else {
                side[v] = (side[u] + 1) % 2;

                q.push(v);
            }
        }
    }
}

bool augmenting_path(int node)
{
    if (tried[node]) {
        return false;
    }

    tried[node] = true;
    for (auto neigh : new_list[node]) {
        if (match[neigh] == -1 || augmenting_path(match[neigh])) {
            match[neigh] = node;
            return true;
        }
    }

    return false;
}

void reach(int node)
{
    if (reachable[node]) {
        return;
    }

    reachable[node] = true;

    for (auto neigh : new_list[node]) {
        if (match[neigh] != node) {
            reach(match[neigh]);
        }
    }
}

void process(int source)
{
    assign_sides(source);

    if (K % 2) {
        if (tot[0].size() < tot[1].size()) {
            swap(tot[0], tot[1]);
        }

        for (auto u : tot[0]) {
            ans[u] = 0;
        }
        for (auto v : tot[1]) {
            ans[v] = 1;
        }

        return;
    }

    for (auto u : tot[0]) {
        for (auto v : tot[1]) {
            if (dist[u][v] < K - 1) {
                new_list[u].pb(v);
                new_list[v].pb(u);
            }
        }
    }

    // First construct the maximum matching

    match.assign(N, -1);
    if (tot[0].size() > tot[1].size()) {
        swap(tot[0], tot[1]);
    }

    for (auto u : tot[0]) {
        tried.assign(N, false);
        augmenting_path(u);
    }

    for (auto v : tot[1]) {
        if (match[v] != -1) {
            match[match[v]] = v;
        }
    }

    // From the left side(tot[0]), get the nodes that are unmatched or can be reached by unmatched with alternating path
    reachable.assign(N, false);
    for (auto u : tot[0]) {
        if (match[u] == -1) {
            reach(u);
        }
    }

    queue<int> q;
    for (auto u : tot[0]) {
        if (reachable[u]) {
            ans[u] = 0;
            q.push(u);
        }
    }

    if (q.empty()) {
        if (tot[0].size() < tot[1].size()) {
            swap(tot[0], tot[1]);
        }
        for (auto u : tot[0]) {
            ans[u] = 0;
            q.push(u);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto v : adj_list[u]) {
            if (ans[v] == -1) {
                ans[v] = ans[u] + 1;
                if (ans[v] >= K) {
                    ans[v] -= 2;
                }
                q.push(v);
            }
        }
    }

    return;
}

void floyd_warshall(void)
{
    for (int i = 0; i < N; i++) {
        dist[i][i] = 0;
        for (auto neigh : adj_list[i]) {
            dist[i][neigh] = 1;
        }
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main(void)
{
    scanf("%d %d %d", &N, &M, &K);

    adj_list.resize(N);
    dist.assign(N, vector<int>(N, INF));
    ans.assign(N, -1);
    side.assign(N, -1);
    new_list.resize(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    floyd_warshall();

    for (int i = 0; i < N; i++) {
        if (side[i] == -1) {
            process(i);
        }
    }

    int res = 0;
    for (int i = 0; i < N; i++) {
        res += ans[i] == 0 || ans[i] == K - 1;
    }

    printf("%d\n", res);
    for (int i = 0; i < N; i++) {
        printf("%d ", ans[i] + 1);
    }
    printf("\n");

    return 0;
}