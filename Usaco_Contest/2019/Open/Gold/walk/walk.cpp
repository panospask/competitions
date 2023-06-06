#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
const int M = 2019201997;

struct dsu {

    int size;
    vector<int> rep;
    int components;
    vector<int> rank;

    void init(int n) {
        size = n;
        components = n;
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
        components--;
        return true;
    }
};

struct Edge {
    int a, b;
    ll w;
};

int n, k;
vector<Edge> edges;
dsu graph;

ll costfunction(int x, int y)
{
    if (x >= y)
        return -1;

    ll a = (ll)2019201913 * x % M;
    ll b = (ll)2019201949 * y % M;

    return (a + b) % M;
}

int main(void)
{
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);

    scanf("%d %d", &n, &k);

    graph.init(n);
    for (int i = 1; i < n; i++) {
        edges.pb({i - 1, i, costfunction(i, i + 1)});
    }

    sort(edges.begin(), edges.end(), [&] (Edge& a, Edge& b) {return a.w < b.w;});

    int c_e = 0;
    while (graph.components > k) {
        graph.unite(edges[c_e].a, edges[c_e].b);
        c_e++;
    }

    ll ans = 0;
    for (int i = n - 2; i >= 0; i--)
        if (graph.find(i) != graph.find(n - 1)) {
            ans = costfunction(i + 1, n);
            break;
        }

    printf("%lld\n", ans);
    return 0;
}