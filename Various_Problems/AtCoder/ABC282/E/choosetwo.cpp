#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

struct dsu {

    int size;
    vector<int> rank;
    vector<int> rep;

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

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (rank[a] == rank[b])
            rank[a]++;
        else if (rank[b] > rank[a])
            swap(a, b);

        rep[b] = a;
        return true;
    }
};

struct Edge {
    int a, b, w;
};

int n, m;
vector<int> a;
vector<Edge> edges;
dsu graph;

int calc_pow(ll a, int b, int m)
{
    ll c = 1;
    while (b) {
        if (b % 2)
            c = c * a % m;

        a = a * a % m;
        b /= 2;
    }

    return c;
}

int main(void)
{
    scanf("%d %d", &n, &m);

    a.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int cost = calc_pow(a[i], a[j], m) + calc_pow(a[j], a[i], m);
            cost %= m;

            edges.pb({i, j, cost});
        }

    sort(edges.begin(), edges.end(), [&] (Edge& a, Edge& b) {return a.w > b.w;});

    graph.init(n);

    ll total_val = 0;
    for (auto& e : edges) {
        if (graph.unite(e.a, e.b))
            total_val += e.w;
    }

    printf("%lld\n", total_val);

    return 0;
}