#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct dsu {

    int size;
    vector<int> rep;
    vector<int> rank;

    void init(int n) {
        size = n;
        rank.assign(n, 0);

        rep.resize(n);
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
        else if (rank[b] > rank[a])
            swap(a, b);

        rep[b] = a;
        return true;
    }
};

struct Edge {
    int a, b, w;
};

int A, B, n, m;
vector<int> verticals;
vector<int> horizontals;
vector<Edge> edges;
dsu graph;
int cur = 0;
map<pi, int> code;


void generate_horizontal_edges(int l, int r, int lthingy)
{
    // Generate the edges for the squares between l and r
    int cost = r - l;

    for (int i = 1; i < horizontals.size(); i++) {
        int d = horizontals[i - 1];
        int u = horizontals[i];

        edges.push_back({lthingy * (m + 1) + i - 1, lthingy * (m + 1) + i, cost});
    }
}

void generate_vertical_edges(int d, int u, int dthingy)
{
    // Generate the edges for the squares between u and d
    int cost = u - d;

    for (int i = 1; i < verticals.size(); i++) {
        int l = verticals[i - 1];
        int r = verticals[i];

        edges.push_back({(i-1) * (m + 1) + dthingy, i * (m + 1) + dthingy, cost});
    }
}

void generate_edges(void)
{
    for (int i = 1; i < verticals.size(); i++) {
        generate_horizontal_edges(verticals[i - 1], verticals[i], i - 1);
    }
    generate_horizontal_edges(verticals.back(), B, verticals.size() - 1);

    for (int i = 1; i < horizontals.size(); i++) {
        generate_vertical_edges(horizontals[i - 1], horizontals[i], i - 1);
    }
    generate_vertical_edges(horizontals.back(), A, horizontals.size() - 1);
}

int main(void)
{
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);

    scanf("%d %d %d %d", &A, &B, &n, &m);

    verticals.resize(n + 1);
    horizontals.resize(m + 1);

    horizontals[0] = verticals[0] = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &verticals[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &horizontals[i]);

    sort(verticals.begin(), verticals.end());
    sort(horizontals.begin(), horizontals.end());

    generate_edges();
    sort(edges.begin(), edges.end(), [&] (Edge& a, Edge& b) {return a.w < b.w;});

    graph.init((n + 1) * (m + 1));

    int rem = (n + 1) * (m + 1);
    ll total_cost = 0;
    for (auto& e : edges) {
        if (graph.unite(e.a, e.b)) {
            total_cost += e.w;
            rem--;
            if (!rem)
                break;
        }
    }

    printf("%lld\n", total_cost);
}