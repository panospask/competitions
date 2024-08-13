#include <bits/stdc++.h>
#define mt make_tuple
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int INF = 1e9 + 5;

int N, M;
int t0, t1, t2;
vector<vector<tuple<int, int, int>>> adj_list;
vector<int> dist;

bool in_call(int t_s, int t_e)
{
    return !(t_s >= t2 || t_e <= t1);
}

bool can_leave(int x)
{
    priority_queue<pi, vector<pi>, greater<pi>> q;
    dist.assign(N, INF);
    dist[0] = x;
    q.push(mp(x, 0));

    while (!q.empty()) {
        int u;
        ll d;

        tie(d, u) = q.top();
        q.pop();

        if (dist[u] != d) {
            continue;
        }
        if (dist[u] > t0) {
            break;
        }

        for (auto [v, l1, l2] : adj_list[u]) {
            ll res = dist[u] + l1;

            if (in_call(dist[u], res)) {
                res = min(dist[u] + l2, t2 + l1);
            }

            if (res < dist[v]) {
                dist[v] = res;
                q.push(mp(dist[v], v));
            }
        }
    }

    return dist[N - 1] <= t0;
}

void solve(void)
{
    scanf("%d %d", &N, &M);

    scanf("%d %d %d", &t0, &t1, &t2);

    adj_list.assign(N, vector<tuple<int, int, int>>());

    for (int i = 0; i < M; i++) {
        int u, v, l1, l2;
        scanf("%d %d %d %d", &u, &v, &l1, &l2);
        u--; v--;

        adj_list[u].pb(mt(v, l1, l2));
        adj_list[v].pb(mt(u, l1, l2));
    }

    int l = -1;
    int r = t0;

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (can_leave(mid)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }    

    printf("%d\n", l);

    return;
}

int main(void) 
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}