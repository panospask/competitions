#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

int N;
vector<int> subtree_size;
vector<vector<pi>> adj_list;
vector<bool> removed;

ll ans = 0;
int BUMP;
vector<pi> cur;
vector<bool> exists;

void calc_subtree(int node, int par, int v)
{
    subtree_size[node] = 1;

    bool made = false;
    if (exists[v + BUMP])
        cur.pb(mp(v, true));
    else {
        made = true;
        exists[v + BUMP] = true;
        cur.pb(mp(v, false));
    }

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh != par && !removed[neigh]) {
            calc_subtree(neigh, node, v + w);
            subtree_size[node] += subtree_size[neigh];
        }
    }

    if (made)
        exists[v + BUMP] = false;
}

int find_centroid(int node, int par, int sz)
{
    for (auto [neigh, w] : adj_list[node])
        if (neigh != par && !removed[neigh] && subtree_size[neigh] > sz / 2)
            return find_centroid(neigh, node, sz);

    return node;
}

ll decompose(int node)
{
    BUMP = subtree_size[node] / 2;
    int c = find_centroid(node, -1, subtree_size[node]);

    vector<vector<int>> d(2 * BUMP + 1, vector<int>(2));

    d[BUMP][false]++;
    removed[c] = true;
    ll res = 0;
    for (auto [neigh, w] : adj_list[c]) {
        if (removed[neigh])
            continue;

        cur.clear();
        calc_subtree(neigh, -1, w);

        for (auto v : cur) {
            if (v.f == 0 && v.s == 0) {
                res += d[BUMP][false] - 1;
            }
            else
                res += d[BUMP - v.f][!v.s];
        }
        for (auto v : cur) {
            for (int i = 0; i <= v.s; i++)
                d[BUMP + v.f][i]++;
        }
    }
    d.clear();

    ans += res;

    for (auto [neigh, w] : adj_list[c]) {
        if (!removed[neigh])
            res += decompose(neigh);
    }

    return res;
}

int main(void)
{
    freopen("yinyang.in", "r", stdin);
    freopen("yinyang.out", "w", stdout);

    scanf("%d", &N);

    adj_list.resize(N);
    subtree_size.resize(N);
    removed.assign(N, false);

    for (int i = 0; i < N - 1; i++) {
        int u, v, t;
        scanf("%d %d %d", &u, &v, &t);
        u--; v--;

        if (!t) t = -1;
        adj_list[u].pb(mp(v, t));
        adj_list[v].pb(mp(u, t));
    }

    BUMP = N;
    exists.assign(2 * N + 1, false);
    calc_subtree(0, -1, 0);
    decompose(0);

    printf("%lld\n", ans);

    return 0;
}