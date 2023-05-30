#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

struct DSU {

    int size;
    vector<int> rep;
    vector<int> component;

    void init(int n) {
        size = n;
        component.assign(size, 1);

        rep.resize(size);
        for (int i = 0; i < n; i++)
            rep[i] = i;
    }

    int find(int a) {
        if (a != rep[a])
            rep[a] = find(rep[a]);

        return rep[a];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return;

        if (component[a] >= component[b]) {
            rep[b] = a;
            component[a] += component[b];
        }
        else {
            rep[a] = b;
            component[b] += component[a];
        }
    }

    int compsize(int a)
    {
        return component[find(a)];
    }
};

struct Edge {
    int a, b, w;
};

bool operator < (const Edge& a, const Edge& b)
{
    return a.w < b.w;
}

int n, q;
DSU d;
vector<Edge> edges;
vector<pair<pi, int>> queries;
vector<int> ans;

int main(void)
{
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);

    scanf("%d %d", &n, &q);
    edges.resize(n - 1);
    queries.resize(q);
    d.init(n);
    ans.resize(q);

    for (int i = 0; i < n - 1; i++) {
        int a, b, r;
        scanf("%d %d %d", &a, &b, &r);
        a--; b--;

        edges[i].a = a;
        edges[i].b = b;
        edges[i].w = r;
    }
    sort(edges.rbegin(), edges.rend());

    for (int j = 0; j < q; j++) {
        int k, u;
        scanf("%d %d", &k, &u);
        u--;
        queries[j] = mp(mp(k, u), j);
    }
    sort(queries.rbegin(), queries.rend());

    int cure = 0;
    for (int j = 0; j < q; j++) {
        int nxt_revel = queries[j].first.first;

        while (cure < n - 1 && edges[cure].w >= nxt_revel) {
            d.unite(edges[cure].a, edges[cure].b);
            cure++;
        }

        // Note: Remove the video itself from the answer
        ans[queries[j].second] = d.compsize(queries[j].first.second) - 1;
    }

    for (int i = 0; i < q; i++)
        printf("%d\n", ans[i]);

    return 0;
}