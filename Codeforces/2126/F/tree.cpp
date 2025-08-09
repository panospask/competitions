#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

int N, Q;
vector<int> color;
vector<vector<pi>> adj_list;
vector<pi> p;
vector<map<int, ll>> kids;

ll ans = 0;

void dfs(int node, int par) {
    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        kids[node][color[neigh]] += w;
        p[neigh] = mp(node, w);
        dfs(neigh, node);

        if (color[neigh] != color[node]) {
            ans += w;
        }
    }
}

void solve(void) {
    scanf("%d %d", &N, &Q);
    color.resize(N);
    adj_list.assign(N, vector<pi>());
    kids.assign(N, map<int, ll>());
    p.resize(N);
    ans = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &color[i]);
    }

    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(mp(v, w));
        adj_list[v].pb(mp(u, w));
    }

    dfs(0, -1);

    while (Q--) {
        int v, x;
        scanf("%d %d", &v, &x);
        v--;

        ans += kids[v][color[v]] - kids[v][x];

        if (v) {
            if (color[p[v].first] == color[v]) {
                ans += p[v].second;
            }
            if (color[p[v].first] == x) {
                ans -= p[v].second;
            }

            kids[p[v].first][color[v]] -= p[v].second;
            kids[p[v].first][x] += p[v].second;
        }

        color[v] = x;
        printf("%lld\n", ans);
    }

    return;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}