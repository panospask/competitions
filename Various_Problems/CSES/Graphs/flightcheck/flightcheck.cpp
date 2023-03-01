#include <bits/stdc++.h>
#define pb push_back
#define MAXN 100000
#define MAXM 200000

using namespace std;

struct edgestruct {
    int to;
    int prev;
};
typedef struct edgestruct Edgestruct;

Edgestruct edges[MAXM + 5];
Edgestruct inv_edges[MAXM + 5];
int head[MAXN + 5];
int inv_head[MAXN + 5];
int n, m;
bool visited[MAXN + 5];

void dfs(int node)
{
    visited[node] = true;
    for (int edge = head[node]; edge != -1; edge = edges[edge].prev)
        if (!visited[edges[edge].to])
            dfs(edges[edge].to);
}

int main(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        head[i] = -1;
        inv_head[i] = -1;
    }
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        edges[i].to = b;
        edges[i].prev = head[a];
        head[a] = i;

        inv_edges[i].to = a;
        inv_edges[i].prev = inv_head[b];
        inv_head[b] = i;
    }

    memset(visited, 0, sizeof(visited));
    dfs(0);
    bool isgood = true;
    int badnode_1 = 0;
    int badnode_2 = -1;
    for (int i = 1; i < n && isgood; i++)
        if (!visited[i]) {
            isgood = false;
            badnode_2 = i;
        }

    if (isgood) {
        for (int i = 0; i < n; i++) 
            head[i] = inv_head[i];
        for (int e = 0; e < m; e++)
            edges[e] = inv_edges[e];

        memset(visited, false, sizeof(visited));
        dfs(0);
        badnode_2 = 0;
        for (int i = 1; i < n && isgood; i++)
            if (!visited[i]) {
                isgood = false;
                badnode_1 = i;
            }
    }

    if (isgood)
        printf("YES\n");
    else 
        printf("NO\n%d %d\n", badnode_1 + 1, badnode_2 + 1);
    
    return 0;
}