#include <bits/stdc++.h>
#define mp make_pair
#define f first
#define s second

using namespace std;

struct UniteTiles {

    int size;
    vector<int> elevation;
    vector<int> rep;
    vector<int> best_lowest;
    vector<vector<int>> kids;

    void init(int n, vector<int>& e) {
        size = n;
        elevation = e;

        kids.resize(n);
        best_lowest.assign(n, -1);

        rep.resize(size);
        for (int i = 0; i < n; i++)
            rep[i] = i;
    }

    int find(int a) {
        if (a != rep[a])
            rep[a] = find(rep[a]);

        return rep[a];
    }

    void dfs(int node, int b_l) {
        if (best_lowest[node] != -1)
            return;

        best_lowest[node] = b_l;
        for (auto& kid : kids[node])
            dfs(kid, b_l);
    }

    void unite(int a, int b, int ele) {
        // Assume the original b is a NEW square
        int or_b = b;

        a = find(a);
        b = find(b);

        if (a == b)
            return;
        if (elevation[b] > elevation[a])
            swap(a, b);

        rep[b] = a;
        kids[a].push_back(b);

        if (elevation[a] > elevation[b]) {
            dfs(b, ele);
        }

        if (elevation[a] > elevation[or_b])
            best_lowest[or_b] = ele;
    }
};

typedef pair<int, int> pi;

const int DIRS = 4;
const int d_i[] = {1, 0, -1, 0};
const int d_j[] = {0, 1, 0, -1};

int n, m;
UniteTiles dsu;
vector<vector<int>> grid;
priority_queue<pair<int, pi>> heights;

int code(int i, int j)
{
    return i * m + j;
}

bool inbound(int i, int j)
{
    return i >= 0 && i < n && j >= 0 && j < m;
}

int main(void)
{
    scanf("%d %d", &n, &m);
    grid.resize(n, vector<int>(m));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
            heights.push(mp(grid[i][j], mp(i, j)));


        }
    vector<int> t(n * m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            t[code(i, j)] = grid[i][j];

    dsu.init(n * m, t);

    while (!heights.empty()) {
        int i , j;
        tie(i, j) = heights.top().s;
        heights.pop();

        for (int x = 0; x < DIRS; x++) {
            int ni = i + d_i[x];
            int nj = j + d_j[x];
            if (inbound(ni, nj) && grid[ni][nj] >= grid[i][j]) {
                // IMPORTANT: ORDER MATTERS
                // Place (i, j) second, it will be checked seperately

                dsu.unite(code(ni ,nj), code(i, j), grid[i][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int ans = max(grid[i][j] - dsu.best_lowest[code(i, j)], 0);
            if (dsu.best_lowest[code(i ,j)] == -1)
                ans = grid[i][j];
            printf("%d ", ans);
        }
        printf("\n");
    }

    return 0;
}