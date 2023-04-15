#include <bits/stdc++.h>
#define MAXK 50000
#define MAXN 50000
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

struct query {
    // Represents the query [l..r)
    int id, l, r;

    void readquery(int i) {
        id = i;
        scanf("%d %d", &l, &r);
        // Make 0-based and open on the right
        l--;
    }
};
typedef struct query Query;

bool operator < (Query& a, Query& b)
{
    // Sort by right endpoint
    return a.r < b.r;
}

struct edge {
    int a, b;

    void readedge(void) {
        scanf("%d %d", &a, &b);
        a--; b--;
    }
};
typedef struct edge Edge;

struct dsu {

    int size;
    int components;
    vector<int> rank;
    vector<int> rep;
    stack<ii> rankchanges;
    stack<ii> repchanges;

    void init(int n) {
        size = components = n;
        rep.resize(size);
        rank.assign(size, 0);

        for (int i = 0; i < size; i++)
            rep[i] = i;

        while (!rankchanges.empty())
            rankchanges.pop();
        while (!repchanges.empty())
            repchanges.pop();
    }

    void save(void) {
        // Add checkpoint
        rankchanges.push(mp(-1, -1));
        repchanges.push(mp(-1, -1));
    }

    void rollback(void) {
        ii cur;
        while (!rankchanges.empty()) {
            cur = rankchanges.top(); rankchanges.pop();
            if (cur.first == -1)
                break;
            rank[cur.first] = cur.second;
        }
        while (!repchanges.empty()) {
            cur = repchanges.top(); repchanges.pop();
            if (cur.first == -1)
                break;
            rep[cur.first] = cur.second;
            components++;
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
            rankchanges.push(mp(a, rank[a]));
            rank[a]++;
        }

        if (rank[b] > rank[a])
            swap(a, b);

        repchanges.push(mp(b, b));
        rep[b] = a;
        components--;
        return;
    }
};

int n, m, k, bucket_size, total_buckets;
vector<Query> buckets[250];
Edge edges[MAXN + 2];
int ans[MAXK + 2];
struct dsu graph;

int main(void)
{
    scanf("%d %d", &n, &m);
    graph.init(n);

    for (int i = 0; i < m; i++) {
        edges[i].readedge();
    }

    scanf("%d", &k);
    bucket_size = sqrt(m);
    total_buckets = m / bucket_size + 2;
    Query cur;
    for (int i = 0; i < k; i++) {
        cur.readquery(i);
        int bucket = cur.l / bucket_size;

        buckets[bucket].push_back(cur);
    }

    for (int b = 0; b < total_buckets; b++) {
        sort(buckets[b].begin(), buckets[b].end());
        // Now proccess the queries
        // Initialize the graph to all different components
        graph.init(n);

        // First those that have right endpoint in the same bucket
        int q = 0;
        Query cur;
        while (q < buckets[b].size()) {
            cur = buckets[b][q];
            if (cur.r / bucket_size != b)
                break;

            graph.save();
            for (int e = cur.l; e < cur.r; e++) {
                graph.unite(edges[e].a, edges[e].b);
            }
            ans[cur.id] = graph.components;
            graph.rollback();

            q++;
        }

        // Next those that have right endpoint in another bucket
        // Start adding edges from the first edge of the next bucket
        int cur_edge = (b + 1) * bucket_size;
        while (q < buckets[b].size()) {
            cur = buckets[b][q];
            while (cur_edge < cur.r) {
                // Add all the edges between the current one and the right endpoint
                graph.unite(edges[cur_edge].a, edges[cur_edge].b);
                cur_edge++;
            }

            // Now save our progress
            graph.save();

            // And add the edges in the bucket with the left endpoint
            for (int e = (b + 1) * bucket_size - 1; e >= cur.l; e--)
                graph.unite(edges[e].a, edges[e].b);

            // Answer our query
            ans[cur.id] = graph.components;

            // And roll back to the latest checkpoint
            graph.rollback();
            q++;
        }
    }

    for (int i = 0; i < k; i++)
        printf("%d\n", ans[i]);

    return 0;
}