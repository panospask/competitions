#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

struct dsu {

    int size;
    vector<int> rep;
    vector<int> dist_from_rep;
    vector<int> rank;

    void init(int n) {
        size = n;
        rep.resize(size);
        dist_from_rep.assign(size, 0);
        rank.assign(size, 0);

        for (int i = 0; i < size; i++)
            rep[i] = i;
    }

    pi find(int a) {
        if (a != rep[a]) {
            pi res = find(rep[a]);
            rep[a] = res.f;
            dist_from_rep[a] = (dist_from_rep[a] + res.s) % 2;
        }

        return mp(rep[a], dist_from_rep[a]);
    }

    bool unite(int a, int b, int edgeweight) {
        int d_a, d_b;
        tie(a, d_a) = find(a);
        tie(b, d_b) = find(b);

        if (a == b) {
            return (d_a + d_b) % 2 == edgeweight % 2;
        }

        if (rank[a] == rank[b])
            rank[a]++;
        if (rank[a] < rank[b])
            swap(a, b);

        rep[b] = a;
        dist_from_rep[b] = (d_a + d_b + edgeweight) % 2;

        return true;
    }

    int dist_between(int a, int b)
    {
        int d_a, d_b;
        tie(a, d_a) = find(a);
        tie(b, d_b) = find(b);

        if (a != b)
            return -1;

        return (d_a + d_b) % 2;
    }
};

int n;
dsu uf;

int main(void)
{
    scanf("%d", &n);

    uf.init(n);

    while (true) {
        int op, a, b;
        scanf("%d %d %d", &op, &a, &b);
        if (op == 0)
            break;

        if (op == 1) {
            bool good = uf.unite(a, b, 0);
            if (!good)
                printf("%d\n", -1);
        }
        else if (op == 2) {
            bool good = uf.unite(a, b, 1);
            if (!good)
                printf("%d\n", -1);
        }
        else if (op == 3) {
            int d = uf.dist_between(a, b);
            if (d == -1 || d % 2)
                printf("0\n");
            else
                printf("1\n");
        }
        else {
            int d = uf.dist_between(a, b);
            if (d == -1 || !(d % 2))
                printf("0\n");
            else
                printf("1\n");
        }
    }

    return 0;
}