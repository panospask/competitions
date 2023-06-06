#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

const int MAXY = 10;

typedef pair<int, int> pi;
typedef long long ll;
typedef pair<ll, int> pli;

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
    int a, b;
    ll w;
};

int n, curcows = 0;
map<pi, int> code;
vector<vector<int>> cows;
vector<vector<int>> best_before;
vector<pi> allcows;
vector<Edge> edges;
dsu graph;

int find(int x, int y)
{
    return code[mp(x, y)];
}

void best_for_cow(int cow_x, int cow_y)
{
    for (int y = 0; y <= MAXY; y++) {
        int pos;
        if (cow_y != y)
            pos = lower_bound(cows[y].begin(), cows[y].end(), cow_x) - cows[y].begin();
        else
            pos = upper_bound(cows[y].begin(), cows[y].end(), cow_x) - cows[y].begin();

        if (pos != cows[y].size())
            best_before[find(cows[y][pos], y)][cow_y] = cow_x;
    }
}

void generate_edges(void)
{
    for (int i = 0; i < n; i++) {
        int cow_x, cow_y;
        tie(cow_x, cow_y) = allcows[i];

        for (int y = 0; y <= MAXY; y++)
            if (best_before[i][y] != -1) {
                ll cost = (ll)(best_before[i][y] - cow_x) * (best_before[i][y] - cow_x) + (y - cow_y) * (y - cow_y);
                edges.pb({i, find(best_before[i][y], y), cost});
            }
    }
}

int main(void)
{
    // freopen("moonetwork.in", "r", stdin);
    // freopen("moonetwork.out", "w", stdout);

    scanf("%d", &n);

    cows.resize(MAXY + 1);
    allcows.resize(n);
    graph.init(n);
    best_before.assign(n, vector<int>(MAXY + 1, -1));

    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        code[mp(x, y)] = i;
        cows[y].push_back(x);
        allcows[i] = mp(x, y);
    }
    for (int y = 0; y <= MAXY; y++)
        sort(cows[y].begin(), cows[y].end());

    for (int i = 0; i <= MAXY; i++)
        for (int j = 0; j < cows[i].size(); j++)
            best_for_cow(cows[i][j], i);
    generate_edges();

    sort(edges.begin(), edges.end(), [&] (Edge& a, Edge& b) {return a.w < b.w;});

    ll total_cost = 0;
    int rem = n;
    for (auto& e : edges) {
        if (graph.unite(e.a, e.b)) {
            total_cost += e.w;
            rem--;
            if (rem == 1)
                break;
        }
    }

    printf("%lld\n", total_cost);
    return 0;
}