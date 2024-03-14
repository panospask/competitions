#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

struct DSU {
    int size;
    vector<int> rep;
    vector<int> rank;

    void init(int n) {
        size = n;
        rep.resize(size);
        rank.assign(size, 0);

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

        if (rank[a] < rank[b])
            swap(a, b);
        if (rank[a] == rank[b])
            rank[a]++;

        rep[b] = a;
        return;
    }
};

struct Query {
    int source;
    int dest;
    int e;
    int id;
};

int N, M, Q;
vector<int> h;
vector<Query> queries;
vector<pi> edges;
vector<bool> ans;
DSU graph;

void solve(void)
{
    scanf("%d %d", &N, &M);

    h.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &h[i]);
    }

    edges.resize(M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &edges[i].first, &edges[i].second);
        edges[i].first--;
        edges[i].second--;

        if (h[edges[i].first] < h[edges[i].second])
            swap(edges[i].first, edges[i].second);
    }

    scanf("%d", &Q);
    queries.resize(Q);
    ans.resize(Q);
    for (int i = 0; i < Q; i++) {
        int a, b, e;
        scanf("%d %d %d", &a, &b, &e);
        a--; b--;

        queries[i] = {a, b, e, i};
    }

    sort(edges.begin(), edges.end(), [] (const pi& a, const pi& b)
                                {return h[a.first] < h[b.first];});
    sort(queries.begin(), queries.end(), [] (const Query& a, const Query& b)
                                {return h[a.source] + a.e < h[b.source] + b.e;});

    graph.init(N);
    int cure = 0;
    for (auto q : queries) {
        while (cure < M && h[edges[cure].first] <= h[q.source] + q.e) {
            graph.unite(edges[cure].first, edges[cure].second);
            cure++;
        }

        ans[q.id] = graph.same(q.source, q.dest);
    }

    for (int i = 0; i < Q; i++) {
        if (ans[i])
            printf("YES\n");
        else
            printf("NO\n");
    }
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}