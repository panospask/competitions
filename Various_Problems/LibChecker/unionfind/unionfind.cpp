#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int N;
    vector<int> rep;

    void init(int n) {
        N = n;

        rep.resize(N);
        for (int i = 0; i < N; i++) {
            rep[i] = i;
        }
    }

    int find(int a) {
        if (rep[a] == a) {
            return a;
        }

        return rep[a] = find(rep[a]);
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        rep[b] = a;
    }
};

int N, Q;
DSU graph;

int main(void)
{
    scanf("%d %d", &N, &Q);

    graph.init(N);

    while (Q--) {
        int op, u, v;
        scanf("%d %d %d", &op, &u, &v);

        if (op == 0) {
            graph.unite(u, v);
        }
        else {
            printf("%d\n", (int)graph.same(u, v));
        }
    }

    return 0;
}