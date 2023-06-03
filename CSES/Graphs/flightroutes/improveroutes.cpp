#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, int> pli;

int n, m, k;
vector<vector<pi>> adj_list;
vector<priority_queue<ll>> dist;

int main(void)
{
    scanf("%d %d %d", &n, &m, &k);

    adj_list.resize(n);
    dist.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(mp(v, w));
    }

    priority_queue<pli, vector<pli>, greater<pli>> q;
    dist[0].push(0);
    q.push(mp(0, 0));

    while (!q.empty()) {
        int v;
        ll d;
        tie(d, v) = q.top();
        q.pop();

        if (dist[v].top() < d) {
            // Not in the top k paths
            continue;
        }

        for (auto e : adj_list[v]) {
            ll val = d + e.s;

            if (dist[e.f].size() < k) {
                dist[e.f].push(val);
                q.push(mp(val, e.f));
            }
            else if (dist[e.f].top() > val) {
                dist[e.f].pop();
                dist[e.f].push(val);
                q.push(mp(val, e.f));
            }
        }
    }

    stack<ll> ans;
    for (int i = 0 ; i < k; i++) {
        ans.push(dist[n - 1].top());
        dist[n - 1].pop();
    }
    while (!ans.empty()) {
        printf("%lld ", ans.top());
        ans.pop();
    }
    printf("\n");

    return 0;
}