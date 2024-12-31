#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int size;
    vector<int> rep;

    // Points to a member of the opposite side
    vector<int> oppose;

    void init(int N) {
        size = N;
        oppose.resize(N);
        rep.resize(N);

        for (int i = 0; i < N; i++) {
            rep[i] = i;
            oppose[i] = -1;
        }
    }

    // Returns the representative of a
    int find(int a) {
        if (a == -1 || rep[a] == a) {
            return a;
        }
        return rep[a] = find(rep[a]);
    }
    // Returns the representative of the opposite set of a
    int opposite(int a) {
        return find(oppose[find(a)]);
    }

    bool enemies(int a, int b) {
        return opposite(a) == find(b);
    }

    // Unite a and b
    // Don't forget to also unite the opposite sets
    bool unite(int a, int b) {
        int r1 = find(a);
        int r2 = find(b);

        int p1 = opposite(r1);
        int p2 = opposite(r2);

        if (r1 == r2) {
            return true;
        }
        if (r1 == p2) {
            return false;
        }

        // Unite(!!!)
        rep[r2] = r1;
        if (p2 != -1 && p1 != -1) {
            rep[p2] = p1;
        }
        if (p1 != -1) {
            oppose[r1] = p1;
            oppose[p1] = r1;
        }
        else if (p2 != -1) {
            oppose[r1] = p2;
            oppose[p2] = r1;
        }

        return true;
    }

    bool make_opposite(int a, int b) {
        int r1 = find(a);
        int p2 = find(b);

        int p1 = opposite(r1);
        int r2 = opposite(p2); 

        if (r1 == r2) {
            return true;
        }
        if (r1 == p2) {
            return false;
        }

        // Unite(!!!)
        if (r2 != -1) {
            rep[r2] = r1;
        }
        if (p1 != -1) {
            rep[p1] = p2;
        }

        oppose[r1] = p2;
        oppose[p2] = r1;

        return true;
    }
};

int N;
vector<vector<int>> grid;
DSU relationship;

void solve(void)
{
    scanf("%d", &N);
    grid.assign(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    relationship.init(N);

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (grid[i][j] > grid[j][i]) {
                relationship.make_opposite(i, j);
            }
            else if (grid[i][j] < grid[j][i]) {
                relationship.unite(i, j);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (relationship.enemies(i, j)) {
                swap(grid[i][j], grid[j][i]);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}