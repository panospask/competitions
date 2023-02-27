#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 200000
#define INF 1000000004

using namespace std;

struct edge {
    long long int r;
    int dest;
    long long int s;
};
typedef struct edge Edge;

bool operator < (const Edge& a, const Edge& b)
{
    return a.r < b.r;
}

multiset<Edge> adj_list[MAXN + 5];
int added_time[MAXN + 5];
int n, m;
int visited[MAXN + 5];

void dfs(int node, int curtime)
{
    if (curtime >= visited[node])
        return;
    
    int prevtime = visited[node];
    visited[node] = curtime;

    Edge fake;
    fake.dest = 0;
    fake.s = 0;
    fake.r = curtime + added_time[node];

    auto it = adj_list[node].lower_bound(fake);

    while (it != adj_list[node].end()) {
        fake = *it;
        if (fake.r >= (long long int)prevtime + added_time[node])  
            break;
        
        dfs(fake.dest, fake.s);
        it++; 
    }
}

int main(void)
{
    // freopen("mroute.in", "r", stdin);
    // freopen("mroute.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        visited[i] = INF;
    }
    visited[0] = 0;

    Edge cur;
    int source;
    for (int i = 0; i < m; i++) {
        scanf("%d %lld %d %lld", &source, &cur.r, &cur.dest, &cur.s);
        cur.dest--;
        source--;
        adj_list[source].insert(cur);
    }
    for (int i = 0; i < n; i++)
        scanf("%d", &added_time[i]);

    for (auto e : adj_list[0]) 
        dfs(e.dest, e.s);

    for (int i = 0; i < n; i++) {
        if (visited[i] != INF)
            printf("%d\n", visited[i]);
        else
            printf("-1\n");
    }
    return 0;
}