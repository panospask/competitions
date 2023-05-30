#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

struct UnionFind {

    int size;
    vector<int> rep;
    vector<int> component;
    int largest;

    void init(int n) {
        size = n;
        component.assign(size, 1);
        largest = 1;

        rep.resize(size);
        for (int i = 0; i < size; i++)
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

        if (component[a] < component[b])
            swap(a, b);

        rep[b] = a;
        component[a] += component[b];

        largest = max(largest, component[a]);
    }
};

struct Edge {
    int a, b;
    int diff;
};

bool operator < (const Edge& a, const Edge& b)
{
    return a.diff < b.diff;
}


int n;
vector<Edge> edges;
vector<vector<int>> grid;
UnionFind dsu;

int code(int i, int j)
{
    return n * i + j;
}

int main(void)
{
    freopen("tractor.in", "r", stdin);
    freopen("tractor.out", "w", stdout);

    scanf("%d", &n);
    grid.resize(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &grid[i][j]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            Edge cur;
            cur.a = code(i, j);

            if (i != n - 1) {
                cur.b = code(i + 1, j);
                cur.diff = abs(grid[i][j] - grid[i + 1][j]);

                edges.pb(cur);
            }
            if (j != n - 1) {
                cur.b = code(i, j + 1);
                cur.diff = abs(grid[i][j] - grid[i][j + 1]);

                edges.pb(cur);
            }
        }
    sort(edges.begin(), edges.end());

    dsu.init(n * n);
    int ans = 0;
    int target = ceil((double)n * n / 2);
    for (int e = 0; e < edges.size(); e++) {
        dsu.unite(edges[e].a, edges[e].b);

        if (dsu.largest >= target) {
            ans = edges[e].diff;
            break;
        }
    }

    printf("%d\n", ans);
    return 0;
}