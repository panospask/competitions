#include <bits/stdc++.h>

using namespace std;

struct dsu {

    int size;
    vector<int> reps;
    vector<int> rank;
    vector<int> values;

    void init(int n) {
        size = n;
        reps.resize(size + 2);
        rank.resize(size + 2);
        for (int i = 0; i < size; i++) {
            reps[i] = i;
            rank[i] = 0;
        }

        values.resize(size + 2);
    }

    void build(int* a) {
        for (int i = 0; i < size; i++)
            values[i] = a[i];
    }

    int get(int i) {
        if (reps[i] != i)
            reps[i] = get(reps[i]);
        
        return reps[i];
    }
    int val(int i) {
        return values[get(i)];
    }

    void unite(int a, int b) {
        a = get(a);
        b = get(b);

        if (rank[a] == rank[b])
            rank[a]++;
        
        if (rank[a] > rank[b]) {
            reps[b] = a;
            values[a] = values[a] + values[b];
        }
        else {
            reps[a] = b;
            values[b] = values[b] + values[a];
        }
    }
};

int n, m;
struct dsu d;

int main(void)
{
    scanf("%d %d", &n, &m);

    d.init(n);
    string com;
    int u, v;
    while (m--) {
        cin >> com >> u >> v;
        u--;
        v--;

        if (com[0] == 'g') {
            bool ans = d.get(u) == d.get(v);

            if (ans) {
                printf("YES\n");
            }
            else 
                printf("NO\n");
        }
        else {
            d.unite(u, v);
        }
    }
}