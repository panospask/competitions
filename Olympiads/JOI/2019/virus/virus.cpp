#include <bits/stdc++.h>
#define CHECK_BIT(val, pos) ((1 << pos) & val)
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e5;

const int DIRS = 4;
const string winds = "SENW";
const int d_x[] = {0, -1, 0, 1};
const int d_y[] = {-1, 0, 1, 0};
// Longest time period that wind blows continuously from the sides defined in the submask
int continuous[1 << DIRS];

struct Node {
    vector<int> members;
    set<int> unlocked_edges;
    map<int, int> locked_edges;

    int size(void) {
        return members.size() + unlocked_edges.size() + locked_edges.size();
    }
    void clear(void) {
        members.clear();
        unlocked_edges.clear();
        locked_edges.clear();
    }
};

int R, C, M;
int N;

vector<int> U;
vector<int> D;
vector<bool> is_immune;
vector<Node> graph;

vector<int> in_graph;

// DFS Variables
vector<bool> vis;
vector<bool> on_cycle;
stack<int> cyc;
vector<int> rep;
vector<int> nxt;

set<int> proc;

bool inside(int i, int j)
{
    return i < R && i >= 0 && j < C && j >= 0;
}

int code(int i, int j)
{
    return C * i + j;
}

void calculate_continuous(int mask)
{
    int best = 0;
    int cur = 0;
    for (int i = 0; i < 2 * M; i++) {
        if (CHECK_BIT(mask, D[i])) {
            cur++;
        }
        else {
            cur = 0;
        }

        best = max(best, cur);
    }

    if (best == 2 * M)
        best = INF;

    continuous[mask] = best;
}

// Returns idx of the new merged node
int merge(int a, int b)
{
    if (graph[a].size() < graph[b].size())
        swap(a, b);

    for (auto mem : graph[b].members) {
        graph[a].members.pb(mem);
        graph[a].unlocked_edges.erase(mem);
        graph[a].locked_edges.erase(mem);
        in_graph[mem] = a;
        rep[mem] = a;
    }

    for (auto v : graph[b].unlocked_edges) {
        if (in_graph[v] == a)
            continue;

        graph[a].unlocked_edges.insert(v);
        graph[a].locked_edges.erase(v);
    }

    for (auto [v, k] : graph[b].locked_edges) {
        if (in_graph[v] == a)
            continue;
        if (graph[a].unlocked_edges.count(v))
            continue;

        int res = graph[a].locked_edges[v] + k;
        if (continuous[res] >= U[v]) {
            graph[a].locked_edges.erase(v);
            graph[a].unlocked_edges.insert(v);
        }
        else {
            graph[a].locked_edges[v] = res;
        }
    }

    graph[b].clear();

    return a;
}

int find(int a)
{
    if (rep[a] != a)
        rep[a] = find(rep[a]);

    return rep[a];
}

void dfs(int node)
{
    if (vis[node]) {
        if (on_cycle[node]) {
            int init = node;
            rep[node] = node;

            while (cyc.top() != init) {
                int v = cyc.top();
                cyc.pop();

                node = merge(node, v);
                rep[v] = node;
            }

            proc.insert(node);
        }

        return;
    }

    vis[node] = true;
    on_cycle[node] = true;
    cyc.push(node);

    int dest = *graph[node].unlocked_edges.begin();
    dfs(dest);

    on_cycle[node] = false;

    nxt[node] = dest;
    rep[node] = rep[dest];
}

void ReadInput(void)
{
    scanf("%d %d %d", &M, &R, &C);

    N = R * C;

    rep.resize(N);
    nxt.resize(N);
    D.resize(2 * M);
    vis.assign(N, false);
    in_graph.resize(N);
    on_cycle.assign(N, false);
    U.resize(R * C);
    graph.resize(R * C);
    is_immune.assign(R * C, false);

    for (int i = 0; i < M; i++) {
        char c;
        scanf(" %c", &c);

        D[i] = D[M + i] = winds.find(c);
    }

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            int v;
            scanf("%d", &v);

            U[code(i, j)] = v;
            if (U[code(i, j)] == 0)
                is_immune[code(i, j)] = true;

            in_graph[code(i, j)] = code(i, j);
        }
}

void InitializeEdges(void)
{
    for (int s = 0; s < (1 << DIRS); s++)
        calculate_continuous(s);

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            int c1 = code(i, j);

            graph[c1].members.pb(c1);

            if (is_immune[c1])
                continue;

            for (int d = 0; d < DIRS; d++) {
                int n_i = i + d_y[d];
                int n_j = j + d_x[d];

                if (!inside(n_i, n_j))
                    continue;

                int c2 = code(n_i, n_j);
                if (is_immune[c2])
                        continue;

                int cur = 1 << d;
                if (continuous[cur] < U[c2]) {
                    graph[c1].locked_edges[c2] = cur;
                }
                else {
                    graph[c1].unlocked_edges.insert(c2);
                }
            }
        }
}

int main(void)
{
    ReadInput();
    InitializeEdges();

    int cnt = 0;
    for (int i = 0; i < N; i++) {
        if (is_immune[i])
            continue;

        cnt += graph[i].unlocked_edges.empty();
    }

    if (cnt) {
        printf("%d\n%d\n", 1, cnt);
        return 0;
    }

    for (int i = 0; i < N; i++)
        if (!vis[i]) {
            dfs(i);
            while (!cyc.empty())
                cyc.pop();
        }

    while (!proc.empty()) {
        int u = *proc.begin();
        proc.erase(u);

        while (graph[u].unlocked_edges.empty() == false) {
            int v = *graph[u].unlocked_edges.begin();
            graph[u].unlocked_edges.erase(v);

            if (find(v) == u) {
                while (in_graph[v] != u) {
                    int c = merge(u, v);
                    rep[u] = c;
                    rep[v] = c;

                    u = c;
                    v = in_graph[nxt[v]];
                }
            }
            else {
                rep[u] = v;
                nxt[u] = v;
                break;
            }
        }
    }

    int min_v = INT_MAX;
    int min_cnt = 0;
    for (int i = 0; i < N; i++) {
        if (find(i) == i && !is_immune[i]) {
            if (min_v > graph[i].members.size()) {
                min_v = graph[i].members.size();
                min_cnt = 0;
            }
            if (min_v == graph[i].members.size()) {
                min_cnt += graph[i].members.size();
            }
        }
    }

    printf("%d\n%d\n", min_v, min_cnt);

    return 0;
}