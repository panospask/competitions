/*
ID: panos.p1
LANG: C++11
TASK: butter
*/

#include <bits/stdc++.h>
#define MAXN 805
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> ii;
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

pqg<ii> q;
bool visited[MAXN];
int dist[MAXN];
int n, c, p;
vector<ii> adj_list[MAXN];
long long int ttl_length[MAXN];
int cownum[MAXN];

void dijkstra(int src)
{
    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= p; i++)
        dist[i] = 10e8;
    
    q.push(mp(0, src));
    ii cur;
    while (!q.empty()) {
        cur = q.top(); q.pop();
        if (!visited[cur.second]) {
            visited[cur.second] = true;
            dist[cur.second] = cur.first;
            for (auto neigh : adj_list[cur.second]) {
                if (!visited[neigh.first])
                    q.push(mp(cur.first + neigh.second, neigh.first));
            }
        }
    }

    ttl_length[src] = 0;
    for (int i = 1; i <= p; i++)
        ttl_length[src] += dist[i] * cownum[i];
}

int main(void)
{
    freopen("butter.in", "r", stdin);
    freopen("butter.out", "w", stdout);

    scanf("%d %d %d", &n, &p, &c);
    int curcow;
    for (int i = 0; i < n; i++) {
        scanf("%d", &curcow);
        cownum[curcow]++;
    }
    int p1, p2, val;
    for (int i = 0; i < c; i++) {
        scanf("%d %d %d", &p1, &p2, &val);
        adj_list[p1].pb(mp(p2, val));
        adj_list[p2].pb(mp(p1, val));
    }

    for (int i = 1; i <= p; i++)
        dijkstra(i);

    long long int ans = 10e15;
    for (int i = 1; i <= p; i++)
        ans = min(ans, ttl_length[i]);

    printf("%lld\n", ans);
    return 0;
}