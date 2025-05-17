#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;

typedef pair<int, int> pi;

const ll INF = 1e18;

int N, M, L;
vector<vector<int>> adj_list;
vector<vector<ll>> dist;

ll minodd = INF;
ll evensum = 0;
ll oddsum = 0;
int oddcnt = 0;

void solve(void) {
    scanf("%d %d %d", &N, &M, &L);

    adj_list.assign(N, vector<int>());
    dist.assign(N, vector<ll>(2, INF));
    evensum = oddcnt = oddsum = 0;
    minodd = INF;

    for (int i = 0; i < L; i++) {
        int v;
        scanf("%d", &v);

        if (v % 2 == 0) {
            evensum += v;
        }
        else {
            oddsum += v;
            oddcnt++;
            minodd = min(minodd, (ll)v);
        }
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    queue<pi> q;
    dist[0][0] = 0;
    q.push(mp(0, 0));
    while (!q.empty()) {
        int u, p;
        tie(u, p) = q.front();
        q.pop();

        for (auto v : adj_list[u]) {
            if (dist[v][!p] == INF) {
                dist[v][!p] = dist[u][p] + 1;
                q.push(mp(v, !p));
            }
        }
    }

    for (int i = 0; i < N; i++) {
        bool doable = false;
        if (dist[i][oddcnt % 2] <= oddsum + evensum) {
            doable = true;
        }
        if (dist[i][!(oddcnt % 2)] <= oddsum + evensum - minodd) {
            doable = true;
        }

        printf("%d", (int)doable);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}