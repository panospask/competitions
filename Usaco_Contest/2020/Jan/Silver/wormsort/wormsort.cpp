#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000
#define MAXM 100000

using namespace std;

typedef pair<int, int> ii;

vector<ii> adj_list[MAXN + 5];
int costs[MAXM + 10];
int p[MAXN + 10];
int n, m;
set<int> to_visit;
bool visited[MAXN + 5];

bool grtcmp(ii a, ii b)
{
    return a.first > b.first;
}

void dfs(int node, int mincost)
{
    if (visited[node])
        return;
    visited[node] = true;
    to_visit.erase(node);

    if (!visited[p[node]])
        to_visit.insert(p[node]);

    for (auto& neigh : adj_list[node]) {
        if (neigh.first < mincost) continue;
        dfs(neigh.second, mincost);
    }
}

bool can_go(int cost)
{
    memset(visited, false, sizeof(visited));
    to_visit.clear();
    bool isgood = true;
    for (int i = 0; i < n && isgood; i++) 
        if (!visited[i]) {
            dfs(i, cost);
            isgood = to_visit.empty();
        }

    return isgood;
}

int main(void)
{
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
        p[i]--;
    }
    int a, b, c;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        a--; b--;
        adj_list[a].pb(mp(c, b));
        adj_list[b].pb(mp(c, a));
        costs[i + 1] = c;
    }   
    costs[0] = INT_MAX;
    sort(costs, costs + m + 1);

    // for (int i = 0; i < n; i++)
    //     sort(adj_list[i].begin(), adj_list[i].end(), grtcmp);

    int l = -1;
    int r = m + 1;
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (can_go(costs[mid]))
            l = mid;
        else 
            r = mid;
    }

    if (l != m)
        printf("%d\n", costs[l]);
    else 
        printf("-1\n");
    return 0;
}