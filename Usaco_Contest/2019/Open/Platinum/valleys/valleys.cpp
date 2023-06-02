#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

struct UnionFind {

    int size;
    vector<int> rep;
    vector<int> sz;

    void init(int n) {
        size = n;
        sz.assign(size, 1);

        rep.resize(size);
        for (int i = 0; i < size; i++)
            rep[i] = i;
    }

    int find(int a) {
        if (rep[a] != a)
            rep[a] = find(rep[a]);

        return rep[a];
    }

    int component(int a) {
        return sz[find(a)];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (sz[b] > sz[a])
            swap(a, b);

        rep[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

const int INF = 1e6 + 5;
const int DIRS_SMALL = 4;
const int DIRS_LARGE = 8;
const int d_i[] = {0, 1, 0, -1, 1, 1, -1, -1};
const int d_j[] = {1, 0, -1, 0, 1, -1, 1, -1};

int n;
vector<vector<int>> grid;
vector<pi> squares;
vector<int> vis;
vector<int> holecount;

vector<int> hole_change;

int code(int i, int j)
{
    return i * n + j;
}
pi decode(int c)
{
    return mp(c / n, c % n);
}

int main(void)
{
    freopen("valleys.in", "r", stdin);
    freopen("valleys.out", "w", stdout);

    scanf("%d", &n);

    // Also pseudo-build the border around with INF height
    squares.resize(n * n);
    n += 2;
    grid.assign(n, vector<int>(n, INF));

    for (int i = 1; i < n - 1; i++)
        for (int j = 1; j < n - 1; j++) {
            scanf("%d", &grid[i][j]);
            squares[(i-1) * (n-2) + j-1] = mp(i, j);
        }
    sort(squares.begin(), squares.end(), [] (const pi& a, const pi& b) -> bool {
        return grid[a.f][a.s] < grid[b.f][b.s];
    });


    UnionFind HoleGraph;
    HoleGraph.init(n * n);
    vis.assign(n * n, false);

    // Build map border
    for (int i = 0; i < n; i++) {
        HoleGraph.unite(0, code(i, 0));
        vis[code(i, 0)] = true;

        HoleGraph.unite(0, code(i, n - 1));
        vis[code(i, n - 1)] = true;

        HoleGraph.unite(0, code(0, i));
        vis[code(0, i)] = true;

        HoleGraph.unite(0, code(n - 1, i));
        vis[code(n - 1, i)] = true;
    }

    // Count the delta in holes created by adding a square
    // Use a dsu to achieve this in reverse order
    hole_change.assign(n * n, 0);

    for (int x = squares.size() - 1; x >= 0; x--) {
        int i, j;
        tie(i, j) = squares[x];
        int curc = code(i, j);

        // Assume that the hole is isolated to begin with
        // (meaning if a block was there, no hole --> reduce holes)
        hole_change[x] = -1;

        for (int d = 0; d < DIRS_LARGE; d++) {
            int ni = i + d_i[d];
            int nj = j + d_j[d];

            if (vis[code(ni, nj)] && HoleGraph.unite(code(ni, nj), curc)) {
                // Merges holes => If we add a block there, the holes will be seperate
                hole_change[x]++;
            }
        }

        vis[code(i, j)] = true;
    }

    // Now add the blocks in normal order
    UnionFind Valleys;
    Valleys.init(n * n);
    vis.assign(n * n, false);
    holecount.assign(n * n, 0);

    ll ans = 0;
    for (int x = 0; x < squares.size(); x++) {
        int i, j;
        tie(i, j) = squares[x];
        int curc = code(i, j);

        for (int d = 0; d < DIRS_SMALL; d++) {
            int ni = i + d_i[d];
            int nj = j + d_j[d];
            if (vis[code(ni, nj)]) {
                int repa = Valleys.find(curc);
                int repb = Valleys.find(code(ni, nj));

                if (repa != repb) {
                    Valleys.unite(repa, repb);
                    holecount[Valleys.find(repa)] = holecount[repa] + holecount[repb];
                }
            }

        }
        holecount[Valleys.find(curc)] += hole_change[x];
        if (holecount[Valleys.find(curc)] == 0)
            ans += Valleys.component(curc);

        vis[curc] = true;
    }

    printf("%lld\n", ans);
}