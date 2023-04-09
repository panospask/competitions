#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

struct edge {
    int a, b;
};
typedef struct edge Edge;

struct dsu {

    int size;
    vector<int> rep;
    vector<int> rank;
    vector<vector<int>> kids;
    vector<int> val;

    void init(int n) {
        size = n;
        rep.resize(size);
        rank.resize(size);
        kids.resize(size);
        val.resize(size);

        for (int i = 0; i < n; i++) {
            rep[i] = i;
            rank[i] = 0;
            val[i] = 0;
        }
    }

    int get(int a) {
        //cout << a << ' ' << rep[a] << endl;
        if (rep[a] != a)
            rep[a] = get(rep[a]);

        return rep[a];
    }

    void unite(int a, int b) {
        a = get(a);
        b = get(b);

        if (a == b)
            return;

        if (rank[a] == rank[b])
            rank[a]++;

        if (rank[a] > rank[b]) {
            rep[b] = a;
            kids[a].push_back(b);
        }
        else {
            rep[a] = b;
            kids[b].push_back(a);
        }
    }

    void assign_all(int a, int v) {
        a = get(a);
        assign_to(a, v);
    }
    void assign_to(int a, int v) {
        val[a] = v;
        // cout << a << ' ' << v << endl;
        for (auto& k : kids[a])
            assign_to(k, v);
    }
};

Edge edges[2 * MAXN + 2];
bool used[MAXN + 1][2];
int holding[MAXN + 1][2];
int n, m;
struct dsu graph;

int main(void)
{
    memset(used, false, sizeof(used));

    scanf("%d %d", &n, &m);
    graph.init(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        holding[i][0] = a;
        holding[i][1] = b;
    }

    for (int i = 0; i < m; i++) {
        int a, h;
        scanf("%d %d", &a, &h);
        a--; h--;
        used[a][h] = true;
        edges[i].a = a;
        edges[i].b = holding[a][h];
    }

    for (int i = 0; i < n; i++) {
        if (!used[i][0]) {
            int a = i;
            int b = holding[i][0];

            if (b >= 0) {
                //cout << a << ' ' << b << endl;
                graph.unite(a, b);
                }
        }
        if (!used[i][1]) {
            int a = i;
            int b = holding[i][1];

            if (b >= 0) {
                //cout << a << ' ' << b << endl;
                graph.unite(a, b);
            }
        }
    }
    graph.assign_all(0, -1);

    // Visit queries backwards
    for (int t = m-1; t >= 0; t--) {
        int a = edges[t].a;
        int b = edges[t].b;

        if (a < 0 || b < 0)
            continue;

        if (graph.get(a) == graph.get(b))
            continue;

        if (graph.get(a) == graph.get(0))
            graph.assign_all(b, t);
        else if (graph.get(b) == graph.get(0))
            graph.assign_all(a, t);

        graph.unite(a, b);
    }

    auto ans = graph.val;
    for (auto t : ans)
        printf("%d\n", t);

    return 0;
}
