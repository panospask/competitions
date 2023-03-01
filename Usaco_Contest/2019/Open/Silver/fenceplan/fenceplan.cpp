#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

typedef pair<int, int> ii;

struct fence {
    int x1, x2, y1, y2;

    fence(int a, int b, int c, int d) {
        x1 = a;
        y1 = b;
        x2 = c; 
        y2 = d;
    }
};
typedef struct fence Fence;

ii coords[MAXN + 5];
vector<int> adj_list[MAXN + 5];
bool visited[MAXN + 5];
int n, m;
int pos_fences = 0;
vector<Fence> fences;

void dfs(int node)
{
    if (visited[node])
        return;

    visited[node] = true;
    fences[pos_fences].x1 = min(fences[pos_fences].x1, coords[node].first);
    fences[pos_fences].y1 = min(fences[pos_fences].y1, coords[node].second);
    fences[pos_fences].x2 = max(fences[pos_fences].x2, coords[node].first);
    fences[pos_fences].y2 = max(fences[pos_fences].y2, coords[node].second);

    for (auto neigh : adj_list[node])   
        dfs(neigh);
}

int main(void)
{
    freopen("fenceplan.in", "r", stdin);
    freopen("fenceplan.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &coords[i].first, &coords[i].second);

    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    for (int i = 0; i < n; i++) 
        if (!visited[i]) {
            fences.pb(Fence(coords[i].first, coords[i].second, coords[i].first, coords[i].second));
            dfs(i);
            pos_fences++;
        }

    int min_per = INT_MAX;
    for (auto f : fences) {
        int curper = 2 * (f.x2 - f.x1 + f.y2 - f.y1);
        min_per = min(min_per, curper);
    }

    printf("%d\n", min_per);
    return 0;
}