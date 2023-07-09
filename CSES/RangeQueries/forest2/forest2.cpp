#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct BIT2D {
    int n, m;
    vector<vector<int>> tree;

    void add(int x, int y, int v) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                tree[i][j] += v;
    }

    int sum(int x, int y) {
        int res = 0;

        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                res += tree[i][j];

        return res;
    }

    int sum(int x1, int y1, int x2, int y2) {
        x1--; y1--;
        return sum(x2, y2) + sum(x1, y1) - sum(x1, y2) - sum(x2, y1);
    }
};

int n, m, q;
vector<vector<int>> grid;

BIT2D b;

int main(void)
{
    scanf("%d %d", &n, &q);
    m = b.m = b.n = n;

    grid.resize(n, vector<int>(m));
    b.tree.resize(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            char c;
            scanf(" %c", &c);
            grid[i][j] = c == '*';
            b.add(i, j, grid[i][j]);
        }

    while (q--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int x, y;
            scanf("%d %d", &x, &y);
            x--; y--;

            if (grid[x][y])
                b.add(x, y, -1);
            else
                b.add(x, y, 1);
            grid[x][y] = !grid[x][y];
        }
        else {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            x1--; y1--; x2--; y2--;

            printf("%d\n", b.sum(x1, y1, x2, y2));
        }
    }

    return 0;
}