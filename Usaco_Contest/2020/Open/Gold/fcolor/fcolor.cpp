#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

struct UnionFind {

    int size;
    vector<int> rep;
    vector<vector<int>> kids;
    vector<int> rank;
    vector<int> col;
    vector<int> admire_rep;

    void init(int n) {
        size = n;
        kids.resize(size);
        rank.assign(size, 0);
        admire_rep.assign(size, -1);
        col.assign(size, -1);

        rep.resize(size);
        for (int i = 0; i < n; i++)
            rep[i] = i;
    }

    bool colour(int a, int c) {
        if (col[a] != -1)
            return false;

        col[a] = c;
        for (auto k : kids[a])
            colour(k, c);

        return true;
    }

    int find(int a) {
        if (a == -1)
            return a;
        if (rep[a] != a)
            rep[a] = find(rep[a]);

        return rep[a];
    }

    int find_admireset(int a) {
        return find(admire_rep[find(a)]);
    }
    void set_admireset(int a, int b) {
        admire_rep[find(a)] = b;
    }

    // Returns representative of new set
    int unite(int a, int b) {
        if (a == -1)
            return b;
        if (b == -1)
            return a;

        a = find(a);
        b = find(b);

        if (a == b)
            return a;

        if (rank[a] == rank[b])
            rank[a]++;
        if (rank[a] < rank[b])
            swap(a, b);

        rep[b] = a;
        kids[a].push_back(b);
        admire_rep[a] = unite(admire_rep[a], admire_rep[b]);

        return a;
    }
};

int n, m;
UnionFind dsu;

int main(void)
{
    freopen("fcolor.in", "r", stdin);
    freopen("fcolor.out", "w", stdout);

    scanf("%d %d", &n, &m);
    dsu.init(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        // b admires a

        if (dsu.find_admireset(a) == -1) {
            // avoid having the a_rep with a set of -1
            dsu.set_admireset(a, b);
        }
        else {
            // unite normally
            dsu.unite(dsu.find_admireset(a), b);
        }
    }

    int curc = 1;
    for (int i = 0; i < n; i++) {
        curc += dsu.colour(dsu.find(i), curc);
        printf("%d\n", dsu.col[i]);
    }

    return 0;
}