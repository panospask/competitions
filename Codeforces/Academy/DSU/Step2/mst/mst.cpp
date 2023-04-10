#include <bits/stdc++.h>
#define MAXE 200000

using namespace std;

struct edge {
    int a, b, w;

    void readedge(void) {
        scanf("%d %d %d", &a, &b, &w);
        a--; b--;
    }
};
typedef struct edge Edge;

struct dsu {

    int size;
    int ttl_disjoint;
    vector<int> rep;
    vector<int> rank;

    void init(int n) {
        size = n;
        ttl_disjoint = n;
        rep.resize(n);
        rank.assign(n, 0);

        for (int i = 0; i < n; i++)
            rep[i] = i;
    }

    int get(int a) {
        if (rep[a] != a)
            rep[a] = get(rep[a]);

        return rep[a];
    }

    void unite(int a, int b) {
        a = get(a);
        b = get(b);

        if (a == b)
            return;

        if (rank[a] == rank[b])
            rank[a]++;

        if (rank[a] > rank[b])
            rep[b] = a;
        else
            rep[a] = b;
        ttl_disjoint--;
    }
};

bool operator < (Edge a, Edge b)
{
    return a.w < b.w;
}

Edge edges[MAXE + 2];
int n, m;
struct dsu graph;

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
        edges[i].readedge();
    graph.init(n);

    long long ttl_weight = 0;
    // Sort by weight
    sort(edges, edges + m);
    for (int i = 0; i < m && graph.ttl_disjoint > 1; i++) {
        if (graph.get(edges[i].a) == graph.get(edges[i].b))
            continue;

        graph.unite(edges[i].a, edges[i].b);
        ttl_weight += edges[i].w;
    }

    printf("%lld\n", ttl_weight);
    return 0;
}
