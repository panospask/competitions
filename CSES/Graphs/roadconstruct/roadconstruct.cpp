#include <bits/stdc++.h>

using namespace std;

struct UnionFind {

    int size, largest;
    int total;
    vector<int> rep;
    vector<int> component;

    void init(int n) {
        size = n;
        component.assign(size, 1);
        largest = 1;
        total = size;

        rep.resize(size);
        for (int i = 0; i < size; i++)
            rep[i] = i;
    }

    int find(int a) {
        if (rep[a] != a)
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
        total--;
    }
};

int n, m;
UnionFind dsu;

int main(void)
{
    scanf("%d %d", &n, &m);

    dsu.init(n);

    while (m--) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        dsu.unite(a, b);

        printf("%d %d\n", dsu.total, dsu.largest);
    }

    return 0;
}