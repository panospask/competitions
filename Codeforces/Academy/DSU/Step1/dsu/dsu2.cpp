#include <bits/stdc++.h>
#define MAXN 300000

using namespace std;

struct item {
    int num;
    int minelement;
    int maxelement;
};
typedef struct item Item;

Item single(int x) 
{
    Item a;

    a.num = 1;
    a.maxelement = a.minelement = x;

    return a;
}

Item merge(Item& a, Item& b)
{
    Item c;
    c.num = a.num + b.num;
    c.maxelement = max(a.maxelement, b.maxelement);
    c.minelement = min(a.minelement, b.minelement);

    return c;
}

struct dsu {

    int size;
    vector<int> reps;
    vector<int> rank;

    vector<Item> values;

    void init(int n) {
        size = n;
        reps.resize(size);
        rank.resize(size);
        values.resize(size);
    }

    void build(int *a) {
        for (int i = 0; i < size; i++) {
            reps[i] = i;
            rank[i] = 0;
            values[i] = single(a[i]);
        }
    }

    int get(int a) {
        if (reps[a] != a) 
            reps[a] = get(reps[a]);

        return reps[a];
    }
    Item getitem(int a) {
        a = get(a);

        return values[a];
    }

    void unite(int a, int b) {
        a = get(a);
        b = get(b);

        if (a==b)
            return;

        if (rank[a] == rank[b])
            rank[a]++;

        if (rank[a] > rank[b]) {
            reps[b] = a;
            values[a] = merge(values[a], values[b]);
        }
        else {
            reps[a] = b;
            values[b] = merge(values[a], values[b]);
        }
    }
};

int n, m;
int a[MAXN + 2];
struct dsu d;

int main(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        a[i] = i+1;

    d.init(n);
    d.build(a);

    string com;
    while (m--) {
        cin >> com;
        if (com[0] == 'u') {
            int u, v;
            scanf("%d %d", &u, &v);
            u--; v--;

            d.unite(u, v);
        }
        else {
            int v;
            scanf("%d", &v);
            v--;

            Item res = d.getitem(v);
            printf("%d %d %d\n", res.minelement, res.maxelement, res.num);
        }
    }

    return 0;
}