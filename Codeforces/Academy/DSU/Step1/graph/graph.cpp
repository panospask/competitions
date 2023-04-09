#include <bits/stdc++.h>
#define MAXK 150000

using namespace std;

struct query {
    int op;
    int a, b;

    void readquery(void) {
        string s;
        cin >> s >> a >> b;
        a--; b--;
        if (s[0] == 'c')
            op = 0;
        else
            op = 1;
    }
};
typedef struct query Query;

struct dsu {

    int size;
    vector<int> rep;
    vector<int> rank;

    void init(int n) {
        size = n;
        rep.assign(size, -1);
        rank.assign(size, 0);
    }

    int get(int a) {
        if (rep[a] != -1)
            return rep[a] = get(rep[a]);
        else
            return a;
    }

    void unite(int a, int b) {
        a = get(a);
        b = get(b);

        if (a == b)
            return;

        if (rank[a] == rank[b])
            rank[a]++;

        if (rank[a] > rank[b])
            rep[b] = a;
        else
            rep[a] = b;
    }
};

int n, m, k;
Query queries[MAXK + 2];
struct dsu graph;

int main(void)
{
    iostream::sync_with_stdio(false);

    cin >> n >> m >> k;
    while (m--) {
        int a, b;
        cin >> a >> b; // Useless
    }
    graph.init(n);

    for (int i = 0; i < k; i++)
        queries[i].readquery();

    // Answer in reverse order
    vector<int> ans;
    for (int i = k - 1; i >= 0; i--) {
        Query cur = queries[i];
        if (cur.op == 0) {
            graph.unite(cur.a, cur.b);
        }
        else {
            int res = graph.get(cur.a) == graph.get(cur.b);
            ans.push_back(res);
        }
    }

    reverse(ans.begin(), ans.end());
    for (auto r : ans) {
        if (r)
            cout << "YES" << '\n';
        else
            cout << "NO" << '\n';
    }

    return 0;
}
