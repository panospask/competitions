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

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (rank[a] == rank[b])
            rank[a]++;
        if (rank[b] > rank[a])
            swap(a, b);

        rep[b] = a;
        return true;
    }
};

struct Edge {
    int a, b, w;
};
bool operator < (const Edge& a, const Edge& b)
{
    return a.w < b.w;
}

int n;
dsu graph;
vector<Edge> edges;

int main(void)
{
    scanf("%d", &n);

    edges.resize(n);
    graph.init(2 * n);

    for (int i = 0; i < n; i++) {
        int c, p1, p2, p3, p4;
        scanf("%d %d %d %d %d", &c, &p1, &p2, &p3, &p4);
        p1--; p2--; p3--; p4--;

        // Consider the portals as vertices
        graph.unite(p1, p2);
        graph.unite(p3, p4);
        edges[i] = {p1, p3, c};
    }

    sort(edges.begin(), edges.end());

    ll ttl_cost = 0;
    for (auto& e : edges) {
        if (graph.unite(e.a, e.b))
            ttl_cost += e.w;
    }

    printf("%lld\n", ttl_cost);
    return 0;
}