#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const ll INF = 1e14;

struct DSU {
    int N;
    // dp[i][j]: Least total latency in the component of i using j servers (I save the slopes, first slope is the one with biggest decrease)
    vector<multiset<ll>> dp;
    // The dp[node][0] of each node (i.e for using 0 servers). It is fake
    vector<ll> in_vl;
    vector<int> cnt;
    vector<int> rep;

    void init(int n, vector<bool>& c) {
        N = n;
        cnt.assign(N, 0);
        dp.assign(N, multiset<ll>());
        rep.assign(N, 0);
        in_vl.assign(N, 0);

        for (int i = 0; i < N; i++) {
            cnt[i] = c[i];
            rep[i] = i;
            if (cnt[i]) {
                // We gain very much by just using a server
                dp[i].insert(-INF);
                in_vl[i] = INF;
            }
            else {
                // We don't gain anything by using a server 
                dp[i].insert(0);
                in_vl[i] = 0;
            }
        }
    }

    int find(int a) {
        if (a != rep[a]) {
            rep[a] = find(rep[a]);
        }
        return rep[a];
    }

    // a holds the final result
    void merge(multiset<ll>& a, multiset<ll>& b) {
        if (a.size() < b.size()) {
            swap(a, b);
        }

        for (auto v : b) {
            a.insert(v);
        }
    }

    void unite(int a, int b, int w) {
        a = find(a);
        b = find(b);

        if (a == b) {
            return;
        }

        // Modify the multisets appropriately
        // Find the first value in both arrays
        ll a1v = in_vl[a] + *dp[a].begin();
        ll b1v = in_vl[b] + *dp[b].begin();
        dp[a].erase(dp[a].begin());
        dp[b].erase(dp[b].begin());
        // Change the initial value to suit the merging
        in_vl[a] = (ll)cnt[a] * w;
        in_vl[b] = (ll)cnt[b] * w;
        dp[a].insert(a1v - in_vl[a]);
        dp[b].insert(b1v - in_vl[b]);

        // Mege the nodes
        merge(dp[a], dp[b]);
        // Set the initial value
        in_vl[a] = (ll)cnt[a] * w + (ll)cnt[b] * w;
        cnt[a] += cnt[b];
        rep[b] = a;
    }

    void print(int node) {
        node = find(node);

        ll cur = in_vl[node];
        int i = 0;
        for (auto slope : dp[node]) {
            i++;
            cur += slope;

            cout << cur << ' ';
        }
        while (i < N) {
            i++;

            cout << cur << ' ';
        }
    }
};

int N, M, P;
DSU graph;
vector<pair<int, pi>> edges;
vector<bool> internet;

void solve(void) {
    cin >> N >> M >> P;

    edges.clear();
    internet.assign(N, false);
    
    for (int i = 0; i < P; i++) {
        int s;
        cin >> s;
        s--;
        internet[s] = true;
    }
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        edges.push_back(pair{w, (pi){u, v}});
    }
    sort(edges.begin(), edges.end());

    graph.init(N, internet);
    for (auto e : edges) {
        graph.unite(e.second.first, e.second.second, e.first);
    }

    graph.print(0);
    cout << endl;
}

int main(void) {
    int T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}