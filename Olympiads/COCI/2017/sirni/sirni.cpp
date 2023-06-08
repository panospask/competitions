#include <bits/stdc++.h>
#define mp make_pair
#define f first
#define s second
#define pb push_back

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

struct dsu {

    int size;
    vector<int> rep;
    vector<int> rank;

    void init(int n) {
        size = n;
        rank.assign(size, 0);

        rep.resize(size);
        for (int i = 0; i < n; i++)
            rep[i] = i;
    }

    int find(int a) {
        if (a != rep[a])
            rep[a] = find(rep[a]);

        return rep[a];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (rank[a] == rank[b])
            rank[a]++;
        else if (rank[b] < rank[a])
            swap(a, b);

        rep[b] = a;
        return true;
    }
};

struct Edge {
    int a, b, w;
};

int n;

const int MAXC = 1e7 + 2;
// const int MAXC = 15 + 2;
const int INF = 1e6;

vector<int> p;
vector<pi> nxt_largest;
vector<vector<pi>> w;
vector<int> first_after;
dsu graph;

int main(void)
{
    scanf("%d", &n);
    w.resize(MAXC + 1);
    graph.init(n);
    first_after.assign(MAXC + 1, INF);

    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        if (first_after[num] == INF) {
            p.push_back(num);
            first_after[num] = p.size() - 1;
        }
    }
    sort(p.begin(), p.end());

    for (int i = 0; i < p.size(); i++)
        first_after[p[i]] = i;
    for (int v = MAXC - 1; v > 0; v--)
        first_after[v] = min(first_after[v], first_after[v + 1]);

    // Generate edges
    for (int i = 0; i < p.size(); i++) {
        int cur = p[i];
        int prvadd = -1;

        int b = first_after[cur + 1];
        if (b == INF)
            break;

        int cost = p[b] % p[i];
        w[cost].pb(mp(i, b));
        prvadd = b;

        for (cur = 2 * p[i]; cur < MAXC; cur += p[i]) {
            int b = first_after[cur];
            if (b == prvadd)
                continue;
            if (b == INF)
                break;

            cost = p[b] % p[i];
            w[cost].pb(mp(i, b));
            prvadd = b;
        }
    }

    // Counting sort
    ll cost = 0;
    for (int i = 0; i < MAXC; i++)
        for (auto& e : w[i])
            if (graph.unite(e.f, e.s))
                cost += i;

    printf("%lld\n", cost);

    return 0;
}