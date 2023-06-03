#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, int> pli;

const ll INF = 1e18;

int n, m, k;

int rooms = 0;
map<pi, int> code;
vector<int> x;
vector<set<int>> level;
vector<bool> visited;
vector<ll> dist;
vector<vector<pair<int, ll>>> adj_list_l;
vector<vector<pair<int, ll>>> adj_list_f;

int find(int i, int j)
{
    if (code.find(mp(i ,j)) == code.end()) {
        code[mp(i, j)] = rooms++;
        adj_list_l.push_back(vector<pair<int, ll>>(0));
        adj_list_f.push_back(vector<pair<int, ll>>(0));
    }

    return code[mp(i, j)];
}

pli find_min(int i)
{
    ll ansd = INF;
    int ansidx = -1;
    for (auto j : level[i]) {
        int idx = find(i, j);
        if (dist[idx] < ansd) {
            ansd = dist[idx];
            ansidx = idx;
        }
    }

    return mp(ansd, ansidx);
}

void solve(void)
{
    adj_list_l.clear();
    adj_list_f.clear();
    level.clear();
    dist.clear();
    visited.clear();
    x.clear();
    code.clear();
    rooms = 0;

    scanf("%d %d %d", &n, &m, &k);

    level.resize(n);
    x.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);

    find(0, 0);
    level[0].insert(0);
    find(n - 1, m - 1);
    level[n - 1].insert(m  - 1);

    for (int e = 0; e < k; e++) {
        int i1, j1, i2, j2, h;
        scanf("%d %d %d %d %d", &i1, &j1, &i2, &j2, &h);
        i1--; j1--; i2--; j2--;

        int idx1 = find(i1, j1);
        int idx2 = find(i2, j2);

        level[i1].insert(j1);
        level[i2].insert(j2);

        adj_list_l[idx1].push_back(mp(idx2, -h));
    }

    for (int i = 0; i < n; i++) {
        int p_j = -1;
        for (auto& j : level[i]) {
            if (p_j != -1) {
                int idx1 = find(i, p_j);
                int idx2 = find(i, j);
                ll cost = (ll) x[i] * abs(j - p_j);

                adj_list_f[idx1].push_back(mp(idx2, cost));
                adj_list_f[idx2].push_back(mp(idx1, cost));
            }

            p_j = j;
        }
    }

    dist.assign(rooms, INF);
    visited.assign(rooms, false);

    priority_queue<pli, vector<pli>, greater<pli>> q;
    dist[0] = 0;

    for (int i = 0; i < n; i++) {

        for (auto j : level[i]) {
            int cd = find(i, j);
            q.push(mp(dist[cd], cd));
        }

        while (!q.empty()) {
            int v = q.top().s;
            q.pop();

            if (v == -1)
                break;
            if (visited[v])
                continue;
            visited[v] = true;

            if (dist[v] == INF)
                break;

            for (auto e : adj_list_f[v]) {
                if (dist[e.f] > dist[v] + e.s) {
                    dist[e.f] = dist[v] + e.s;
                    q.push(mp(dist[e.f], e.f));
                }
            }
            for (auto e : adj_list_l[v])
                dist[e.f] = min(dist[e.f], dist[v] + e.s);
        }
    }

    ll ans = dist[find(n - 1, m - 1)];
    if (ans != INF)
        printf("%lld\n", ans);
    else
        printf("NO ESCAPE\n");

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}