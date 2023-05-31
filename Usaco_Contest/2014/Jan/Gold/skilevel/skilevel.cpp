#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

struct UnionFind {

    int n, t;
    vector<int> rep;
    vector<int> minreq;
    vector<vector<int>> kids;
    vector<int> size;

    void init(int n, int t) {
        this->t = t;
        this->n = n;
        kids.resize(n);
        size.assign(n, 1);
        minreq.assign(n, -1);

        rep.resize(n);
        for (int i = 0; i < n; i++)
            rep[i] = i;
    }

    int find(int a) {
        if (a != rep[a])
            rep[a] = find(rep[a]);

        return rep[a];
    }

    void dfs(int i, int w) {
        minreq[i] = w;
        for (auto kid : kids[i])
            dfs(kid, w);
    }

    void unite(int a, int b, int w) {
        a = find(a);
        b = find(b);

        if (a == b)
            return;

        if (size[a] < size[b])
            swap(a, b);

        if (size[a] + size[b] >= t) {
            if (size[a] < t)
                dfs(a, w);
            if (size[b] < t)
                dfs(b, w);
        }

        rep[b] = a;
        kids[a].push_back(b);
        size[a] += size[b];
    }
};

struct Edge {
    int a, b, w;
};

bool operator < (const Edge& a, const Edge& b)
{
    return a.w < b.w;
}

int n, m, t;
vector<vector<int>> grid;
vector<Edge> edges;
UnionFind dsu;

int code(int i, int j)
{
    return i * n + j;
}

int main(void)
{
    freopen("skilevel.in", "r", stdin);
    freopen("skilevel.out", "w", stdout);

    scanf("%d %d %d", &m, &n, &t);

    if (t == 1) {
        printf("%d\n", 0);
        return 0;
    }

    grid.resize(m, vector<int>(n));
    dsu.init(n * m, t);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &grid[i][j]);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (i + 1 < m) {
                int d = abs(grid[i][j] - grid[i + 1][j]);

                Edge cur = {code(i, j), code(i + 1, j), d};
                edges.push_back(cur);
            }

            if (j + 1 < n ) {
                int d = abs(grid[i][j] - grid[i][j + 1]);

                Edge cur = {code(i, j), code(i, j + 1), d};
                edges.push_back(cur);
            }
        }

    sort(edges.begin(), edges.end());

    for (auto& e : edges) {
        dsu.unite(e.a, e.b, e.w);
    }

    long long ans = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            int startpoint;
            scanf("%d", &startpoint);
            if (startpoint)
                ans += dsu.minreq[code(i, j)];
        }

    printf("%lld\n", ans);
    return 0;
}