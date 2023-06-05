#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, int> pli;
typedef pair<ll, pi> plp;

struct Edge {
    int dest;
    int colour;
    int price;
};

int n, m;
vector<map<int, ll>> colourcost;
vector<map<int, bool>> visited;
vector<map<int, ll>> dist;
vector<map<int, vector<Edge>>> by_colour;

vector<vector<Edge>> adj_list;

int main(void)
{
    scanf("%d %d", &n, &m);

    adj_list.resize(n);
    colourcost.resize(n);
    dist.resize(n);
    by_colour.resize(n);
    visited.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v, c, p;
        scanf("%d %d %d %d", &u, &v, &c, &p);
        u--; v--;

        colourcost[u][c] += p;
        by_colour[u][0].pb({v, c, p});
        by_colour[u][c].pb({v, c, p});

        colourcost[v][c] += p;
        by_colour[v][0].pb({u, c, p});
        by_colour[v][c].pb({u, c, p});
    }

    priority_queue<plp, vector<plp>, greater<plp>> q;
    dist[0][0] = 0;
    q.push(mp(0, mp(0, 0)));

    while (!q.empty()) {
        int v, c;
        tie(v, c) = q.top().s;
        q.pop();

        if (visited[v][c])
            continue;
        visited[v][c] = true;


        for (auto e : by_colour[v][c]) {
            ll current_cost = colourcost[v][e.colour] - e.price;

            //Add normally first, by colour later
            if (c == 0)
                current_cost = min(current_cost, (ll)e.price);

            if ((dist[e.dest].find(0) == dist[e.dest].end())
                || (dist[e.dest][0] > dist[v][c] + current_cost)) {
                    dist[e.dest][0] = dist[v][c] + current_cost;
                    q.push(mp(dist[e.dest][0], mp(e.dest, 0)));
                }

            if (c == 0) {
                // Add by colour only, c has to be equal to 0
                // Force next step to be in same colour => The weight of the edge will be counted later
                if ((dist[e.dest].find(e.colour) == dist[e.dest].end())
                    || (dist[e.dest][e.colour] > dist[v][c])) {
                        dist[e.dest][e.colour] = dist[v][c];
                        q.push(mp(dist[e.dest][e.colour], mp(e.dest, e.colour)));
                    }
            }
        }
    }

    if (dist[n - 1].find(0) == dist[n - 1].end()) {
        printf("%d\n", -1);
    }
    else {
        ll ans = dist[n - 1][0];
        printf("%lld\n", ans);
    }

    return 0;
}