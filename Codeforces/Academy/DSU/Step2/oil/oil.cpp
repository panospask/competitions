#include <bits/stdc++.h>
#define MAXM 100000

using namespace std;

typedef pair<int, int> ii;

struct edge {
    int a, b, w;
    int ind;

    void readedge(int i) {
        scanf("%d %d %d", &a, &b, &w);
        a--; b--;
        ind = i;
    }
    bool operator < (struct edge& a) {
        return w < a.w;
    }
};
typedef struct edge Edge;

struct dsu {

    int size; 
    vector<int> rep;
    vector<int> rank;

    void init(int n) {
        size = n;
        rep.resize(n);
        rank.assign(n, 0);

        for (int i = 0; i < n; i++)
            rep[i] = i;
    }

    int get(int a) {
        if (a != rep[a])
            rep[a] = get(rep[a]);

        return rep[a];
    }

    bool unite(int a, int b) {
        a = get(a);
        b = get(b);
        
        if (a == b) 
            return false;

        if (rank[a] == rank[b])
            rank[a]++;

        if (rank[a] > rank[b])
            rep[b] = a;
        else 
            rep[a] = b;

        return true;
    }
};

int n, m;
long long s;
bool used[MAXM + 2];
Edge edges[MAXM + 2];
struct dsu graph;

int main(void)
{
    scanf("%d %d %lld", &n, &m, &s);
    graph.init(n);
    for (int i = 0; i < m; i++)
        edges[i].readedge(i);

    // Build the maximum spanning tree, all other edges are candidates for removal
    sort(edges, edges + m);
    reverse(edges, edges + m);
    int components = n;

    for (auto e : edges) {
        if (graph.unite(e.a, e.b)) {
            used[e.ind] = true;
            components++;
            if (components == 1)
                break;
        }
    }

    reverse(edges, edges + m);
    // Start removing the lower value edges first so more can fit

    int removed = 0;
    set<int> ids;
    for (int i = 0; i < m && edges[i].w <= s; i++) {
        if (!used[edges[i].ind]) {
            s -= edges[i].w;
            removed++;
            ids.insert(edges[i].ind);
        }
    }

    printf("%d\n", removed);
    for (auto id : ids)
        printf("%d ", id + 1);
    printf("\n");
    return 0;
}