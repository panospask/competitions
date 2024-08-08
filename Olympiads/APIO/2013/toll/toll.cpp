#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

struct DSU {
    int N;
    vector<int> rep;
    vector<int> rank;

    void clear(void) {
        rep.clear();
        rank.clear();
    }

    void init(int n) {
        N = n;
        rep.resize(N);
        rank.assign(N, 0);

        for (int i = 0; i < N; i++) {
            rep[i] = i;
        }
    }

    int find(int a) {
        if (rep[a] == a) {
            return a;
        }

        return rep[a] = find(rep[a]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) {
            return false;
        }
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        if (rank[a] == rank[b]) {
            rank[a]++;
        }

        rep[b] = a;
        return true;
    }
};

struct Edge {
    int a, b;
    int w;
    int id;

    bool operator < (const Edge& b) {
        return this->w < b.w;
    }
};

bool idsort(const Edge& a, const Edge& b)
{
    return a.id < b.id;
}

struct SuperEdge {
    int dest;
    int w;
    bool is_default;
};

int N, M, K;
vector<int> p;
vector<Edge> edges;
vector<pi> greedy;

vector<vector<pi>> init_list;
vector<bool> used;
vector<bool> vital;

DSU tree;

// Adjacency list and people counter for the compressed MST
vector<vector<SuperEdge>> adj_list;
vector<ll> tot;
vector<int> pos;

// opt[mask]: The MST with the most profit(i.e highest toll prices on Mr. Greedy edges) when considering only the Mr.Greedy edges in mask
vector<vector<SuperEdge>> opt[1 << 20];
vector<bool> possible;

ll profit = 0;
int maxw;
vector<bool> in_path;

void build_mst(bool save)
{
    sort(edges.begin(), edges.end());

    DSU graph;
    graph.init(N);

    for (int i = 0; i < edges.size(); i++) {
        bool cur = graph.unite(edges[i].a, edges[i].b);

        if (save) {
            if (cur) {
                used[edges[i].id] = true;
                init_list[edges[i].a].pb(mp(edges[i].b, edges[i].id));
                init_list[edges[i].b].pb(mp(edges[i].a, edges[i].id));
            }
        }
        else {
            if (!cur && used[edges[i].id]) {
                // This is an edge that has to go when building MST with Mr.Greedy's edges
                vital[edges[i].id] = true;
            }
        }
    }
}

void calculate_msts(void)
{
    used.assign(M, false);
    vital.assign(M, false);
    init_list.resize(N);

    build_mst(true);

    for (int i = 0; i < K; i++) {
        edges.pb({greedy[i].first, greedy[i].second, 0, M});
    }

    build_mst(false);

    sort(edges.begin(), edges.end(), idsort);
}

// Run dfs on the initial MST and compress it
void compress(int node, int par)
{
    for (auto [neigh, id] : init_list[node]) {
        if (neigh == par) {
            continue;
        }

        compress(neigh, node);

        if (!vital[id]) {
            tree.unite(neigh, node);
        }
    }
}

void merge_compressed(void)
{
    pos.assign(N, -1);

    int sz = 0;
    for (int i = 0; i < N; i++) {
        if (pos[tree.find(i)] == -1) {
            pos[tree.find(i)] = sz;
            sz++;
            adj_list.push_back({});
            tot.push_back(0);
        }

        tot[pos[tree.find(i)]] += p[i];
    }

    for (int i = 0; i < N; i++) {
        for (auto [neigh, id] : init_list[i]) {
            if (vital[id]) {
                adj_list[pos[tree.find(i)]].push_back({pos[tree.find(neigh)], edges[id].w, true});
            }
        }
    }

    for (int i = 0; i < K; i++) {
        greedy[i].first = pos[tree.find(greedy[i].first)];
        greedy[i].second = pos[tree.find(greedy[i].second)];
    }
}

void read_input(void)
{
    scanf("%d %d %d", &N, &M, &K);

    edges.resize(M);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        edges[i] = {u, v, w, i};
    }

    greedy.resize(K);
    for (int i = 0; i < K; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        greedy[i] = mp(u, v);
    }

    p.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &p[i]);
    }
}

void clear(void)
{
    edges.clear();
    p.clear();
    greedy.clear();
    init_list.clear();
    used.clear();
    pos.clear();
    tree.clear();
    vital.clear();
}

void dfs(int node, int par, int dest, int mask)
{
    if (node == dest) {
        in_path[node] = true;
        return;
    }

    for (auto e : opt[mask][node]) {
        if (e.dest == par) {
            continue;
        }

        dfs(e.dest, node, dest, mask);
        if (in_path[e.dest]) {
            in_path[node] = true;
            if (e.is_default) {
                maxw = max(maxw, e.w);
            }
            break;
        }
    }
}

ll calc(int node, int par, int mask)
{
    ll people = tot[node];
    for (auto e : opt[mask][node]) {
        if (e.dest == par) {
            continue;
        }

        ll res = calc(e.dest, node, mask);
        if (e.is_default == false) {
            profit += res * e.w;
        }

        people += res;
    }

    return people;
}

int main(void)
{
    read_input();

    calculate_msts();

    tree.init(N);
    compress(0, -1);
    merge_compressed();

    clear();


    N = adj_list.size();
    // Start calculating the MST while including a subset of Mr. Greedy's edges

    ll ans = 0;

    opt[0] = adj_list;
    possible.assign(1 << K, false);
    possible[0] = true;
    adj_list.clear();

    for (int s = 1; s < (1 << K); s++) {
        // Find the Mr.Greedy edge to add last
        int to_add = 0;
        while (!CHECK_BIT(s, to_add)) {
            to_add++;
        }

        int prv = s - (1 << to_add);
        if (!possible[prv]) {
            continue;
        }

        int x = greedy[to_add].first;
        int y = greedy[to_add].second;

        in_path.assign(N, false);
        maxw = 0;

        dfs(x, -1, y, prv);

        if (maxw == 0) {
            continue;
        }

        possible[s] = true;
        opt[s].resize(N);
        for (int i = 0; i < N; i++) {
            for (auto e : opt[prv][i]) {
                if (!in_path[i] || !in_path[e.dest]) {
                    opt[s][i].pb(e);
                }
                else {
                    e.w = min(e.w, maxw);
                    if (e.w == maxw && e.is_default) {
                        // This is the edge to be removed
                        continue;
                    }

                    opt[s][i].pb(e);
                }
            }
        }
        opt[s][x].pb({y, maxw, false});
        opt[s][y].pb({x, maxw, false});

        profit = 0;
        calc(pos[tree.find(0)], -1, s);
        ans = max(ans, profit);

        if (to_add == K - 1 || CHECK_BIT(prv, to_add + 1)) {
            opt[prv].clear();
        }
        if (CHECK_BIT(s, 0)) {
            opt[s].clear();
        }
    }

    printf("%lld\n", ans);

    return 0;
}