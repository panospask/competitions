#include <bits/stdc++.h>

using namespace std;

struct dsu {

    int size;
    vector<int> rep;
    vector<int> rank;
    vector<int> value;
    vector<int> mod_top_by;

    void init(int n) {
        size = n;
        rep.resize(size);
        rank.resize(size);
        value.resize(size);
        mod_top_by.resize(size);

        for (int i = 0; i < n; i++) {
            rep[i] = i;
            rank[i] = 0;
            value[i] = 0;
            mod_top_by[i] = 0;
        }
    }

    int get(int a) {
        if (rep[a] != a)
            return get(rep[a]);
        else
            return a;
    }
    int get_res(int a) {
        int ans = value[get(a)];
        while (a != get(a)) {
            ans += mod_top_by[a];
            a = rep[a];
        }

        return ans;
    }

    void add(int u, int val) {
        u = get(u);
        value[u] += val;

        return;
    }

    void unite(int u, int v) {
        u = get(u);
        v = get(v);
        if (u == v)
            return;

        if (rank[u] == rank[v])
            rank[u]++;

        if (rank[u] > rank[v]) {
            // Join u to v
            mod_top_by[v] = value[v] - value[u];
            //cerr << "MOD: " << mod_top_by[v] << endl;
            rep[v] = u;
        }
        else {
            // Join u to v
            mod_top_by[u] = value[u] - value[v];
            rep[u] = v;
            //cerr << "MOD: " << mod_top_by[u] << endl;
        }
    }
};

int n, m;
dsu unionstruct;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin >> n >> m;

    unionstruct.init(n);

    string op;
    while (m--) {
        cin >> op;
        if (op[0] == 'j') {
            int u, v;
            cin >> u >> v;
            u--; v--;

            unionstruct.unite(u, v);
        }
        else if (op[0] == 'a') {
            int u, x;
            cin >> u >> x;
            u--;

            unionstruct.add(u, x);
        }
        else {
            int u;
            cin >> u;
            u--;

            int ans = unionstruct.get_res(u);
            cout << ans << '\n';
        }
    }

    return 0;
}
