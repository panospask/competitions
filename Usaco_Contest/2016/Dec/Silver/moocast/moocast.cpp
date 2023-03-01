#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 200

using namespace std;

typedef pair<int, int> ii;

vector<int> adj_list[MAXN + 5];
int n;
ii cows[MAXN + 5];
int p[MAXN + 5];
bool visited[MAXN + 5];
int curnodes = 0;

void dfs(int node)
{
    if (visited[node])
        return ;

    visited[node] = true;
    curnodes++;
    for (auto neigh : adj_list[node])
        dfs(neigh);
}

int main(void)
{
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d %d", &cows[i].first, &cows[i].second, &p[i]);

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int dist = (cows[i].first - cows[j].first) * (cows[i].first - cows[j].first) + (cows[i].second - cows[j].second) * (cows[i].second - cows[j].second);
            if (dist <= p[i] * p[i])
                adj_list[i].pb(j);
            if (dist <= p[j] * p[j])
                adj_list[j].pb(i);
        }

    int maxnodes = 0;
    for (int i = 0; i < n; i++) {
        curnodes = 0;
        memset(visited, false, sizeof(visited));
        dfs(i);
        maxnodes = max(maxnodes, curnodes);
    }

    printf("%d\n", maxnodes);
    return 0;
}