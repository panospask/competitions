#include <bits/stdc++.h>

using namespace std;

struct dsu {

    int size;
    vector<int> rep;
    vector<int> rank;

    void init(int n) {
        size = n;
        rank.assign(size, 0);

        rep.resize(size);
        for (int i = 0; i < size; i++)
            rep[i] = i;
    }

    int find(int a) {
        if (rep[a] != a)
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
    int a, b, w, id;
};

int n, m, k;
vector<int> ans;
vector<dsu> kidgraphs;
vector<Edge> edges;

int main(void)
{
    scanf("%d %d %d", &n, &m, &k);
    edges.resize(m);
    kidgraphs.resize(k);
    ans.resize(m);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;
        edges[i] = {u, v, w, i};
    }
    sort(edges.begin(), edges.end(), [&] (Edge& a, Edge& b) {return a.w > b.w;});

    for (int kid = 0; kid < k; kid++) {
        kidgraphs[kid].init(n);
    }

    for (auto& e : edges) {

        int l = -1; // l always has e.a and e.b united
        int r = k; // r never has e.a and e.b united

        while (r > l + 1) {
            int mid = (l + r) / 2;
            if (kidgraphs[mid].same(e.a, e.b))
                l = mid;
            else
                r = mid;
        }

        if (r != k) {
            kidgraphs[r].unite(e.a, e.b);
            ans[e.id] = r;
        }
        else
            ans[e.id] = -1;
    }

    for (int i = 0; i < m; i++)
        printf("%d\n", ans[i] + 1);

    return 0;
}