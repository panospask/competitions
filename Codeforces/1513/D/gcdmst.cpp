#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

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
        if (rank[b] < rank[a])
            swap(a, b);

        rep[b] = a;
        return true;
    }
};

struct Edge {
    int a, b, w;
};

int n, p;
vector<int> a;
vector<int> divides_left;
vector<Edge> edges;
vector<bool> used;
dsu graph;

ll kruskals(void)
{
    sort(edges.begin(), edges.end(), [&] (Edge& a, Edge& b) {return a.w < b.w;});
    graph.init(n);

    ll ans = 0;
    for (auto& e : edges) {
        if (graph.unite(e.a, e.b))
            ans += e.w;
    }

    return ans;
}

void solve(void)
{
    scanf("%d %d", &n, &p);

    a.resize(n);
    edges.clear();
    divides_left.resize(n);
    used.assign(n, false);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);

        divides_left[i] = i;

        if (i != n - 1)
            edges.pb({i, i + 1, p});
    }

    for (int i = 0; i < n; i++) {
        int rdiv = i;
        while (rdiv < n && a[rdiv] % a[i] == 0)
            rdiv++;

        if (rdiv == n || a[rdiv] % a[i]) {
            for (int j = i + 1; j < rdiv; j++) {
                edges.pb({i, j, a[i]});
            }
        }

        i = rdiv - 1;
    }
    for (int i = n - 1; i >= 0; i--) {
        int ldiv = i - 1;
        while (ldiv >= 0 && a[ldiv] % a[i] == 0)
            ldiv--;

        if (ldiv == -1 || a[ldiv] % a[i]) {
            for (int j = i - 1; j > ldiv; j--) {
                edges.pb({i, j, a[i]});
            }
        }

        i = ldiv + 1;
    }

    ll ans = kruskals();
    printf("%lld\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}