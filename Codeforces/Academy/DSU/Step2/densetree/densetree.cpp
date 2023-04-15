#include <bits/stdc++.h>
#define MAXM 10000

using namespace std;

struct edge {
    int a, b, w;

    void readedge(void) {
        scanf("%d %d %d", &a, &b, &w);
        a--; b--;
    }
};
typedef struct edge Edge;

bool operator < (Edge a, Edge b)
{
    return a.w < b.w;
}

struct dsu {

    int size;
    vector<int> rep;
    vector<int> rank;

    void init(int n) {
        size = n;
        rep.resize(size);
        rank.assign(size, 0);
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

Edge edges[MAXM + 2];
int n, m;
struct dsu graph;

int main(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
        edges[i].readedge();

    sort(edges, edges + m);
    long long ans = INT_MAX;
    for (int i = 0; i < m; i++) {
        // What if i was the lowest value edge
        int diff = -edges[i].w;
        int components = n;
        graph.init(n);
        int j = i;
        while (j < m && components > 1) {
            if (graph.unite(edges[j].a, edges[j].b))
                components--;
            j++;
        }
        j--;
        if (components == 1) {
            diff += edges[j].w;
            ans = min(ans, (long long)diff);
        }

    }

    if (ans == INT_MAX)
        printf("NO\n");
    else {
        printf("YES\n%lld\n", ans);
    }

    return 0;
}