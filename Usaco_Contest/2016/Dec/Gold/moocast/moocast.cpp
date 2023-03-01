#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

typedef pair<int, int> ii;

int n;
ii coords[MAXN + 5];
vector<ii> dist[MAXN + 5];
bool visited[MAXN + 5];
int curvis = 0;

void dfs(int node, int x)
{
    if (visited[node])
        return;

    visited[node] = true;
    curvis++;
    for (int i = 0; i < n - 1 && dist[node][i].first <= x; i++) {
        dfs(dist[node][i].second, x);
    }
}

bool can_visit_all(int x)
{
    memset(visited, 0, sizeof(visited));
    curvis = 0;
    dfs(0, x);

    return curvis == n;
}

int main(void)
{
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coords[i].first, &coords[i].second);
    }

    int curdist;
    for (int i = 0; i < n; i++) 
        for (int j = i + 1; j < n; j++) {
            curdist = (coords[i].first - coords[j].first) * (coords[i].first - coords[j].first) + (coords[i].second - coords[j].second) * (coords[i].second - coords[j].second);
            dist[i].pb(mp(curdist, j));
            dist[j].pb(mp(curdist, i));
        }

    for (int i = 0; i < n; i++)
        sort(dist[i].begin(), dist[i].end());

    int l = 0; // can_visit_all(l) = false
    int r = dist[0][n-2].first; // can_visit_all(r) = true
    while (r > l + 1) {
        auto m = (l + r) / 2;
        if (can_visit_all(m))
            r = m;
        else 
            l = m;
    }

    printf("%d\n", r);
    return 0;
}