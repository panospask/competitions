#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MAXV = 1e9;

struct DSU {
    int size;
    int components;
    vector<int> rep;
    vector<int> rank;

    void init(int n) {
        size = n;
        components = n;

        rank.assign(size, 0);
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

        components--;
        if (rank[a] < rank[b])
            swap(a, b);
        if (rank[a] == rank[b])
            rank[a]++;

        rep[b] = a;
        return;
    }
};

DSU graph;
int N;
vector<int> l, r, c, p;

vector<pi> furthest;

bool lsort(const int& a, const int& b)
{
    return l[a] < l[b];
}

void process(void)
{
    furthest.assign(2, {-1, -1});
    sort(p.begin(), p.end(), lsort);

    for (int t = 0; t < N; t++) {
        int i = p[t];

        if (furthest[!c[i]].f >= l[i]) {
            graph.unite(i, furthest[!c[i]].s);
        }

        furthest[c[i]] = max(furthest[c[i]], mp(r[i], i));
    }
}

int solve(void)
{
    scanf("%d", &N);

    graph.init(N);
    r.resize(N);
    l.resize(N);
    c.resize(N);
    p.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &c[i], &l[i], &r[i]);
        p[i] = i;
    }

    process();

    for (int i = 0; i < N; i++) {
        p[i] = i;
        l[i] = MAXV - l[i];
        r[i] = MAXV - r[i];
    }

    process();

    printf("%d\n", graph.components);

    return 0;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}