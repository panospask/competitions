#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const ll INF = 1e14;

struct DSU {
    int N;
    // dp[i][j]: Least total latency in the component of i using j servers
    vector<vector<ll>> dp;
    vector<int> cnt;
    vector<int> rep;

    void init(int n, vector<bool>& c) {
        N = n;
        cnt.assign(N, 0);
        dp.assign(N, vector<ll>());
        rep.assign(N, 0);

        for (int i = 0; i < N; i++) {
            cnt[i] = c[i];
            rep[i] = i;
            if (cnt[i]) {
                dp[i].push_back(INF);
                dp[i].push_back(0);
            }
            else {
                dp[i].push_back(0);
            }
        }
    }

    int find(int a) {
        if (a != rep[a]) {
            rep[a] = find(rep[a]);
        }
        return rep[a];
    }

    void unite(int a, int b, int w) {
        a = find(a);
        b = find(b);

        if (a == b) {
            return;
        }

        // Merge the dps
        // Either use all in a, all in b, or a combination
        vector<ll> res(cnt[a] + cnt[b] + 1, INF);
        for (int v1 = 0; v1 <= cnt[a]; v1++) {
            for (int v2 = 0; v2 <= cnt[b]; v2++) {
                // What if we choose v1 from a and v2 from b
                res[v1 + v2] = min(res[v1 + v2], dp[a][v1] + dp[b][v2]);
            }
        }
        // Alternatively choose everything from a => Everyone in b gets latency w
        for (int v1 = 1; v1 <= cnt[a]; v1++) {
            res[v1] = min(res[v1], dp[a][v1] + (ll)w * cnt[b]);
        }
        for (int v2 = 1; v2 <= cnt[b]; v2++) {
            res[v2] = min(res[v2], dp[b][v2] + (ll)w * cnt[a]);
        }

        // Mege the nodes
        dp[a] = res;
        cnt[a] += cnt[b];
        rep[b] = a;
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

    int tot = graph.find(0);
    for (int k = 1; k <= N; k++) {
        if (k > P) {
            cout << 0 << ' ';
            continue;
        }
        cout << graph.dp[tot][k] << ' ';
    }
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