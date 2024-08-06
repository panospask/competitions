#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct DSU {
    int N;
    vector<int> rep;
    vector<int> sz;

    void init(int n) {
        N = n;
        rep.resize(N);
        sz.assign(N, 1);

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

    int size(int a) {
        return sz[find(a)];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) {
            return;
        }

        if (sz[a] < sz[b]) {
            swap(a, b);
        }

        rep[b] = a;
        sz[a] += sz[b];
    }
};

int N, M;
vector<vector<int>> adj_list;
vector<int> degree;
vector<bool> used;
vector<int> order;
DSU graph;

// Order nodes by their degree while constantly removing the lowest degree node
void order_nodes(void)
{
    priority_queue<pi, vector<pi>, greater<pi>> q;

    for (int i = 0; i < N; i++) {
        degree[i] = adj_list[i].size();
        q.push(mp(degree[i], i));
    }

    while (!q.empty()) {
        int u, d;
        tie(d, u) = q.top();
        q.pop();

        if (used[u] || degree[u] != d) {
            continue;
        }

        used[u] = true;
        order.pb(u);

        for (auto neigh : adj_list[u]) {
            if (!used[neigh]) {
                degree[neigh]--;
                q.push(mp(degree[neigh], neigh));
            }
        }
    }

    reverse(order.begin(), order.end());
}

int main(void)
{
    scanf("%d %d", &N, &M);

    adj_list.resize(N);
    used.assign(N, false);
    degree.assign(N, 0);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    order_nodes();

    graph.init(N);
    used.assign(N, false);

    ll ans= 0;
    for (int i = 0; i < N; i++) {
        int u = order[i];
        used[u] = true;

        for (auto neigh : adj_list[u]) {
            if (used[neigh]) {
                graph.unite(u, neigh);
            }
        }

        ans = max(ans, (ll)graph.size(u) * degree[u]);
    }

    printf("%lld\n", ans);

    return 0;
}