#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct dsu {

    int size;
    vector<int> rep;
    vector<int> rank;

    void init(int n) {
        size = n;
        rank.assign(size, 0);

        rep.resize(size);
        for (int i = 0; i < n; i++)
            rep[i] = i;
    }

    int find(int a) {
        if (a != rep[a])
            rep[a] = find(rep[a]);

        return rep[a];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return;

        if (rank[a] == rank[b])
            rank[a]++;
        if (rank[b] > rank[a])
            swap(a, b);

        rep[b] = a;
    }
};

struct Edge {
    int a, b, w;
};
bool operator < (const Edge& a, const Edge& b)
{
    return a.w < b.w;
}

int n, m;
vector<Edge> edges;
dsu graph;

int main(void)
{
    scanf("%d %d", &n, &m);

    edges.resize(m);

    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        a--; b--;

        edges[i] = {a, b, w};
    }
    sort(edges.begin(), edges.end());

    ll cost = 0;
    graph.init(n);
    int components = n;
    for (auto e : edges) {
        if (!graph.same(e.a, e.b)) {
            graph.unite(e.a, e.b);
            cost += e.w;
            components--;
        }
    }

    if (components > 1)
        printf("IMPOSSIBLE\n");
    else
        printf("%lld\n", cost);

    return 0;
}