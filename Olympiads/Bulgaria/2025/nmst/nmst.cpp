#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

const int MOD = 1e9 + 7;
const int MAXVAL = 1e6;

typedef long long ll;
typedef pair<int, int> pi;

struct DSU {
    int size;
    vector<int> rep;
    vector<int> rank;

    vector<tuple<int, int, int>> operations;

    void init(int N) {
        size = N;
        rep.assign(size, 0);
        rank.assign(size, 0);
        operations.clear();

        for (int i = 0; i < N; i++) {
            rep[i] = i;
        }
    }

    int find(int a) {
        if (a != rep[a]) {
            int prv = rep[a];
            rep[a] = find(rep[a]);
            if (rep[a] != prv)
                operations.push_back({a, -1, prv});
        }
        return rep[a];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) {
            return false;
        }

        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        operations.push_back({a, b, rank[a]});

        if (rank[a] == rank[b]) {
            rank[a]++;
        }

        rep[b] = a;
        return true;
    }

    void rollback(void) {
        reverse(operations.begin(), operations.end());
        for (auto [a, b, rankA] : operations) {
            if (b != -1) {
                rep[b] = b;
                rank[a] = rankA;
            }
            else {
                rep[a] = rankA;
            }
        }

        operations.clear();

    }

    void checkpoint(void) {
        operations.clear();
    }
};

int N, M;
DSU graph;
vector<vector<pi>> edges;

int main(void) {
    scanf("%d %d", &N, &M);

    graph.init(N);
    edges.resize(MAXVAL + 5);
    for (int i = 0; i < M; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        u--; v--;

        edges[c].push_back({u, v});
    }

    ll ans = 1;
    for (int v = 0; v <= MAXVAL; v++) {
        graph.checkpoint();

        int T = edges[v].size();

        // Do it once with all to see where it gets you
        int cnt = 0;
        for (int i = 0; i < T; i++) {
            cnt += graph.unite(edges[v][i].first, edges[v][i].second);
        }
        graph.rollback();

        int possible = cnt == 0 ? 1 : 0;
        int mask = (1 << cnt) - 1;
        while(cnt && mask < (1 << T)) {
            if (__builtin_popcount(mask) == cnt) {
                bool good = true;
                for (int i = 0; i < T; i++) {
                    if (CHECK_BIT(mask, i)) {
                        if (graph.unite(edges[v][i].first, edges[v][i].second) == false) {
                            good = false;
                        }
                    }
                }
                if (good) {
                    possible++;
                }

                graph.rollback();

                int c = mask & -mask;
                int r = mask + c;
                mask = (((r ^ mask) >> 2) / c) | r;
            }
        }

        ans = ans * possible % MOD;

        // Add everything once again
        for (int i = 0; i < T; i++) {
            graph.unite(edges[v][i].first, edges[v][i].second);
        }
    }

    printf("%lld\n", ans);
}