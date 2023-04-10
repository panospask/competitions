#include <bits/stdc++.h>

using namespace std;

struct dsu {

    int size;
    vector<int> rep;
    vector<int> dist_to_top;

    void init(int n) {
        size = n;
        rep.resize(size);
        dist_to_top.assign(size, 0);
        for (int i = 0; i < size; i++)
            rep[i] = i;
    }

    //(x, y) is the leader and the distance to him
    pair<int, int> get(int a) {
        if (rep[a] != a) {
            pair<int, int> ans = get(rep[a]);
            rep[a] = ans.first;
            dist_to_top[a] += ans.second;
        }
        return make_pair(rep[a], dist_to_top[a]);
    }

    // Make boss a sub of boss b
    void unite(int a, int b) {
        rep[a] = b;
        dist_to_top[a] = 1;
    }
};

int n, m;
struct dsu Company;

int main()
{
    scanf("%d %d", &n, &m);
    Company.init(n);

    int op;
    while (m--) {
        scanf("%d", &op);
        if (op == 1) {
            int x, y;
            scanf("%d %d", &x, &y);
            x--; y--;

            Company.unite(x, y);
        }
        else {
            int x;
            scanf("%d", &x);
            x--;

            int ans = Company.get(x).second;
            printf("%d\n", ans);
        }
    }
    return 0;
}
