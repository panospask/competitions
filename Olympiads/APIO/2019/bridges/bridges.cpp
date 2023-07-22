#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

struct DSU {
    int size;
    vector<int> rep;
    vector<int> sz;
    stack<int> upd;

    void init(int n) {
        size = n;
        sz.assign(size, 1);
        while (!upd.empty())
            upd.pop();

        rep.resize(size);
        for (int i = 0; i < n; i++)
            rep[i] = i;
    }
    void clear(void) {
        init(size);
    }

    void save(void) {
        upd.push(-1);
    }
    void rollback(void) {
        while (upd.top() != -1) {
            sz[rep[upd.top()]] -= sz[upd.top()];
            rep[upd.top()] = upd.top();

            upd.pop();
        }
        upd.pop();
    }

    int find(int a) {
        while (rep[a] != a)
            a = rep[a];

        return a;
    }
    int component(int a) {
        return sz[find(a)];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return;

        if (sz[a] < sz[b])
            swap(a, b);

        upd.push(b);
        sz[a] += sz[b];
        rep[b] = a;

        return;
    }
};

struct Edge {
    int a, b, w;
    int id;

    bool operator < (const Edge& b) {
        return this->w < b.w;
    }
};
struct Update {
    int edge;
    int v;
    int time;

    bool operator < (const Update& b) {
        return this->time < b.time;
    }
};
struct Query {
    int id;
    int s;
    int v;
    int time;

    bool operator < (const Query& b) {
        return this->v < b.v;
    }
};

int N, M, Q;
int BLOCK_SIZE;
vector<Edge> edges;
vector<Edge> original_edges;
vector<bool> changed;
vector<int> ans;

DSU graph;

void process_block(vector<Update>& updates, vector<Query>& queries)
{
    graph.clear();

    sort(queries.rbegin(), queries.rend());
    sort(updates.rbegin(), updates.rend());
    for (auto& u : updates) {
        changed[u.edge] = true;
    }

    int cure = 0;
    for (auto& q : queries) {
        while (cure < M && edges[cure].w >= q.v) {
            if (!changed[edges[cure].id])
                graph.unite(edges[cure].a, edges[cure].b);

            cure++;
        }

        graph.save();
        for (auto& u : updates) {
            if (u.time > q.time)
                continue;
            if (!changed[u.edge])
                continue;

            // mark this edge
            changed[u.edge] = false;
            if (u.v < q.v)
                continue;

            int a = original_edges[u.edge].a;
            int b = original_edges[u.edge].b;
            graph.unite(a, b);
        }
        for (auto& u : updates) {
            if (u.time < q.time)
                continue;
            if (!changed[u.edge])
                continue;

            changed[u.edge] = false;
            int a, b, v;
            a = original_edges[u.edge].a;
            b = original_edges[u.edge].b;
            v = original_edges[u.edge].w;

            if (v < q.v)
                continue;
            graph.unite(a, b);
        }
        for (auto& u : updates) {
            changed[u.edge] = true;
        }

        ans[q.id] = graph.component(q.s);
        graph.rollback();
    }

    for (auto& u : updates) {
        changed[u.edge] = false;
    }
}

int main(void)
{
    scanf("%d %d", &N, &M);

    changed.resize(M);
    graph.init(N);

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        edges.push_back({u, v, w, i});
        original_edges.push_back({u, v, w, i});
    }
    edges = original_edges;
    sort(edges.rbegin(), edges.rend());

    scanf("%d", &Q);

    // BLOCK_SIZE = sqrt(Q);
    BLOCK_SIZE = 1000;

    vector<Query> queries;
    vector<Update> updates;
    for (int i = 0; i < Q; i++) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int id, v;
            scanf("%d %d", &id, &v);
            id--;

            updates.push_back({id, v, i});
        }
        else {
            int s, v;
            scanf("%d %d", &s, &v);
            s--;

            queries.push_back({(int)ans.size(), s, v, i});
            ans.push_back(0);
        }

        if (i % BLOCK_SIZE == BLOCK_SIZE - 1) {
            process_block(updates, queries);

            reverse(updates.begin(), updates.end());
            for (auto& u : updates) {
                original_edges[u.edge].w = u.v;
            }
            edges = original_edges;
            sort(edges.rbegin(), edges.rend());

            updates.clear();
            queries.clear();
        }
    }
    process_block(updates, queries);

    for (int i = 0; i < ans.size(); i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}