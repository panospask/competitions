#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int MAXD = 1e9;
const int MAXC = 2e5 + 1;

int N, M, B, E;
vector<vector<pi>> adj_list;
vector<int> dist;
vector<vector<int>> colours;
vector<int> active;

void clear(void)
{
    for (auto c : active) {
        colours[c].clear();
        dist[c] = MAXD;
    }

    active.clear();
}

void solve(void)
{
    scanf("%d %d", &N, &M);

    adj_list.assign(N, vector<pi>());

    for (int i = 0; i < M; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        u--; v--; c--;

        adj_list[u].pb(mp(v, c));
        adj_list[v].pb(mp(u, c));
        colours[c].pb(u);
        colours[c].pb(v);
        active.pb(c);
    }

    scanf("%d %d", &B, &E);
    B--; E--;

    if (B == E) {
        printf("0\n");
        clear();
        return;
    }

    queue<int> q;

    for (auto e : adj_list[B]) {
        if (dist[e.second] != MAXD)
            continue;

        dist[e.second] = 1;
        q.push(e.second);
    }
    adj_list[B].clear();

    int ans = -1;
    bool found = false;
    while (!q.empty() && !found) {
        int c = q.front();
        q.pop();

        for (auto v : colours[c]) {
            if (v == E) {
                found = true;
                ans = dist[c];
            }

            for (auto e : adj_list[v]) {
                if (dist[e.second] == MAXD) {
                    dist[e.second] = dist[c] + 1;
                    q.push(e.second);
                }
            }
            adj_list[v].clear();
        }
    }

    printf("%d\n", ans);

    clear();
}

int main(void)
{
    int t;
    scanf("%d", &t);

    dist.assign(MAXC, MAXD);
    colours.assign(MAXC, vector<int>());

    while (t--) {
        solve();
    }

    return 0;
}