#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int n;
vector<vector<int>> dist;
vector<pi> shortestedge;
vector<bool> used;
vector<vector<pi>> adj_list;

void DIE(void)
{
    printf("NO\n");
    exit(EXIT_SUCCESS);
}

int find_best(void)
{
    int bdist = 1e9 + 1;
    int bnode = -1;
    for (int i = 0; i < n; i++) {
        if (!used[i] && shortestedge[i].first < bdist) {
            bdist = shortestedge[i].first;
            bnode = i;
        }
    }

    return bnode;
}

void check_good(int node, int par, int source, ll c)
{
    if (c != dist[node][source])
        DIE();

    for (auto neigh : adj_list[node])
        if (neigh.first != par)
            check_good(neigh.first, node, source, c + neigh.second);
}

int main(void)
{
    scanf("%d", &n);
    adj_list.resize(n);
    used.assign(n, false);
    dist.resize(n, vector<int>(n));
    shortestedge.assign(n, mp(1e9 + 1, -1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            scanf("%d", &dist[i][j]);
            if (dist[i][j] != dist[j][i])
                DIE();
        }
        scanf("%d", &dist[i][i]);
        if (dist[i][i] != 0)
            DIE();

        for (int j = i + 1; j < n; j++) {
            scanf("%d", &dist[i][j]);
            if (dist[i][j] <= 0)
                DIE();
        }
    }

    // Pick arbitrary node to start prim's
    shortestedge[0] = mp(0, -1);
    for (int i = 0; i < n; i++) {
        int v, par;
        v = find_best();
        par = shortestedge[v].second;
        used[v] = true;

        // Insert kid-parent edge
        if (par != -1) {
            adj_list[v].pb(mp(par, dist[v][par]));
            adj_list[par].pb(mp(v, dist[par][v]));
        }

        // Check that the distance matrix is correct thus far
        check_good(v, -1, v, 0);

        // Update other nodes
        for (int j = 0; j < n; j++) {
            if (used[j])
                continue;

            if (shortestedge[j].first > dist[j][v]) {
                shortestedge[j] = mp(dist[j][v], v);
            }
        }
    }

    printf("YES\n");
    return 0;
}