#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> ii;

struct dsu {

    int size;
    int components;
    vector<int> rep;
    vector<int> rank;
    stack<ii> repchange;
    stack<ii> rankchange;

    void init(int n) {
        size = components = n;
        rank.assign(n, 0);

        rep.resize(n);
        for (int i = 0; i < n; i++)
            rep[i] = i;

        while (!repchange.empty())
            repchange.pop();
        while (!rankchange.empty())
            rankchange.pop();
    }

    void save(void) {
        repchange.push(mp(-1, -1));
        rankchange.push(mp(-1, -1));
    }

    void rollback(void) {
        ii cur;
        while (!repchange.empty()) {
            cur = repchange.top(); repchange.pop();
            if (cur.first == -1)
                break;
            rep[cur.first] = cur.second;
            components++;
        }
        while (!rankchange.empty()) {
            cur = rankchange.top(); rankchange.pop();
            if (cur.first == -1)
                break;
            rank[cur.first] = cur.second;
        }
    }

    int get(int a) {
        if (a != rep[a])
            return get(rep[a]);
        
        return a;
    }

    void unite(int a, int b) {
        a = get(a);
        b = get(b);

        if (a == b)
            return;

        if (rank[a] == rank[b]) {
            rankchange.push(mp(a, rank[a]));
            rank[a]++;
        }
        else if (rank[a] < rank[b])
            swap(a, b);

        repchange.push(mp(b, rep[b]));
        rep[b] = a;
        components--;

        return;
    }
};

struct edge {
    int a, b;
    int l, r;
};
typedef struct edge Edge;

int n, m;
struct dsu graph;
map<int, int> ans;
vector<Edge> total_e;
vector<int> total_q;
map<ii, int> edgefind;

bool intersect(ii a, ii b) 
{
    if (a.first >= b.second || b.first >= a.second)
        return false;
    return true;
}

// Calculate all queries in (l, r]
void calculate(int l, int r, vector<Edge>& edges, vector<int> queries)
{
    if (l == r - 1) {
        graph.save();
        for (auto& e : edges) {
            if (e.l <= l && e.r >= r)
                graph.unite(e.a, e.b);
        }

        for (auto& q : queries) {
            if (q == l) {
                ans[l] = graph.components;
                break;
            }
        }

        graph.rollback();
        return;
    }

    vector<int> kidqueries;
    vector<Edge> kidedges;
    graph.save();

    for (auto& e : edges) {
        if (e.l <= l && r <= e.r) {
            // All the subsequent queries can use this edge 
            graph.unite(e.a, e.b);
        }
        else if (intersect(mp(e.l, e.r), mp(l, r))) {
            kidedges.pb(e);
        }
    }
    for (auto& q : queries) {
        if (l <= q && q < r)
            kidqueries.pb(q);
    }
    int mid = (l + r) / 2;
    calculate(l, mid, kidedges, kidqueries);
    calculate(mid, r, kidedges, kidqueries);

    graph.rollback();
}

int main(void)
{
    scanf("%d %d", &n, &m);
    graph.init(n);

    char op;
    int a, b;
    if (m == 0)
        return 0;

    for (int i = 0; i < m; i++) {
        scanf(" %c", &op);
        if (op == '+') {
            Edge c;
            scanf("%d %d", &a, &b);
            a--; b--;

            edgefind[mp(a,b)] = total_e.size();
            c.a = a;
            c.b = b;
            c.l = i;
            c.r = m;
            total_e.pb(c);
        }
        else if (op == '-') {
            scanf("%d %d", &a, &b);
            a--; b--;

            total_e[edgefind[mp(a,b)]].r = i + 1;
        }
        else {
            total_q.pb(i);
        }
    }

    edgefind.clear();
    calculate(0, m, total_e, total_q);

    for (auto p : ans)
        printf("%d\n", p.second);

    return 0;
}