#include <bits/stdc++.h>

using namespace std;

struct dsu {

    int n;
    int levels;
    vector<int> rep;
    vector<vector<int>> anc;
    vector<vector<int>> val;
    vector<int> rank;
    vector<int> depth;

    void init(int n) {
        this->n = n;
        levels = log2(n) + 1;
        anc.assign(levels, vector<int>(n + 3, n));
        val.assign(levels, vector<int>(n + 3, 1e9));
        rank.assign(n, 0);
        depth.assign(n, 0);

        rep.resize(n);
        for (int i = 0; i < n; i++)
            rep[i] = i;
    }

    void inserted_all(void) {
        // Calculate ancestors
        for (int i = 0; i < n; i++) {
            int a = anc[0][i];
            while (a != n) {
                a = anc[0][a];
                depth[i]++;
            }
        }

        anc[0][n] = n;
        for (int up = 1; up < levels; up++)
            for (int i = 0; i <= n; i++) {
                anc[up][i] = anc[up - 1][anc[up - 1][i]];
                val[up][i] = max(val[up - 1][i], val[up - 1][anc[up - 1][i]]);
            }
    }

    int find(int a) {
        if (a != rep[a])
            return find(rep[a]);

        return a;
    }

    void unite(int a, int b, int v) {
        a = find(a);
        b = find(b);

        if (a == b)
            return;

        if (rank[a] == rank[b])
            rank[a]++;

        if (rank[a] > rank[b]) {
            rep[b] = a;
            anc[0][b] = a;
            val[0][b] = v;
        }
        else {
            rep[a] = b;
            anc[0][a] = b;
            val[0][a] = v;
        }
    }

    pair<int, int> jump(int a, int up) {
        int v = 0;
        for (int i = 0; i < levels; i++)
            if (up & (1<<i)) {
                v = max(v, val[i][a]);
                a = anc[i][a];
            }

        return make_pair(a, v);
    }

    int find_dist(int a, int b) {
        if (find(a) != find(b))
            return -1;

        if (depth[a] < depth[b])
            swap(a, b);

        int v = 0;
        tie(a, v) = jump(a, depth[a] - depth[b]);

        if (a == b)
            return v;

        for (int up = levels - 1; up >= 0; up--) {
            int oa = anc[up][a];
            int ob = anc[up][b];

            if (oa != ob) {
                v = max(v, val[up][a]);
                v = max(v, val[up][b]);

                a = oa;
                b = ob;
            }
        }

        v = max(v, val[0][a]);
        v = max(v, val[0][b]);

        return v;
    }
};

int n, m, q;
dsu u;

int main(void)
{
    scanf("%d %d %d", &n, &m, &q);

    u.init(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        u.unite(a, b, i + 1);
    }

    u.inserted_all();
    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        printf("%d\n", u.find_dist(a, b));
    }

    return 0;
}