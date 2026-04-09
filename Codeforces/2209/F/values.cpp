#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int INF = 1e6;

int N, K;
vector<vector<int>> adj_list;
vector<int> A;

vector<pi> furthest, secfurth;

ll ans = 0;

struct BestLeafs {
    int N, K;

    ll sum = 0;
    vector<ll> values;
    multiset<ll> good;
    multiset<ll> bad;

    void init(int n, int k) {
        K = k;
        N = n;
        sum = 0;
        values.assign(n, 0);
        good.clear();
        bad.clear();

        for (int i = 0; i < K; i++) {
            good.insert(0);
        }
        for (int i = K; i < N; i++) {
            bad.insert(0);
        }
    }

    // Add +v to the value of said leaf
    void update(int i, ll v) {
        ll prv = values[i];
        add(v + prv);
        remove(prv);
        values[i] = v + prv;
    }

    ll total(void) {
        return sum;
    }

    void add(ll v) {
        sum += v;
        good.insert(v);

        if (good.size() == K + 1) {
            sum -= *good.begin();
            bad.insert(*good.begin());
            good.erase(good.begin());
        }
    }

    void remove(ll v) {
        if (good.find(v) != good.end()) {
            sum -= v;
            good.erase(good.find(v));

            sum += *prev(bad.end());
            good.insert(*prev(bad.end()));
            bad.erase(prev(bad.end()));
        }
        else {
            bad.erase(bad.find(v));
        }
    }
};

BestLeafs leafs;

pi operator + (pi a, pi b) {
    return {a.first + b.first, a.second + b.second};
}

void dfs(int node, int par) {
    if (adj_list[node].size() <= 1) {
        furthest[node] = {0, -node};
    }

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        pi cur = furthest[neigh] + pi{1, 0};
        if (cur > furthest[node]) {
            swap(cur, furthest[node]);
        }
        if (cur > secfurth[node]) {
            swap(cur, secfurth[node]);
        }
    }

    leafs.update(-furthest[node].second, A[node]);
}

void reroot(int node, int par, pi par_furthest) {
    // Find answer

    // Remove current value
    leafs.update(-furthest[node].second, -A[node]);
    ans = max(ans, A[node] + leafs.total());

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        pi cur = furthest[node];
        if (furthest[node].second == furthest[neigh].second) {
            cur = secfurth[node];
        }

        cur = max(cur, par_furthest);
        
        // This is where node's value will go if the parent of it is neigh
        leafs.update(-cur.second, A[node]);

        reroot(neigh, node, cur + pi{1, 0});

        leafs.update(-cur.second, -A[node]);
    }

    // Don't forget to add back original value
    leafs.update(-furthest[node].second, +A[node]);
}

void solve(void) {
    scanf("%d %d", &N, &K);

    adj_list.assign(N, vector<int>());
    A.resize(N);
    leafs.init(N, K - 1);
    furthest.assign(N, {-INF, -1});
    secfurth.assign(N, {-INF, -1});

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    // Find a nonleaf root for start
    int v = 0;
    while (adj_list[v].size() == 1 && v < N - 1) {
        v++;
    }

    ans = 0;
    dfs(v, -1);
    reroot(v, -1, {-INF, -1});

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}