/*
ID: panos.p1
LANG: C++11
TASK: butter
*/

#include <bits/stdc++.h>
#define MAXN 805
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

int connect[MAXN][MAXN];
int n, p, c;
int cownum[MAXN];
long long int dist[MAXN];
long long int ans;
ii adj_list[MAXN];
set<ii> q;
bool visited[MAXN];

void floyd(void)
{
    for (int k = 1; k <= p; k++)
        for (int i = 1; i <= p; i++)
            for (int j = 1; j <= p; j++) 
                connect[i][j] = min(connect[i][j], connect[i][k] + connect[j][k]);
}

// void dijkstra(int src)
// {
//     memset(visited, false, n + 5);
//     q.insert(mp(0, src));

//     ii cur;
//     while (!q.empty()) {
//         cur = *(q.begin());

//     }
// }

void calc_dist(void)
{
    for (int i = 1; i <= p; i++)
        for (int j = 1; j <= p; j++)
            dist[i] += connect[i][j] * cownum[j];
}
void find_shortest_dist(void)
{
    ans = LONG_LONG_MAX;
    for (int i = 1; i <= p; i++)
        ans = min(ans, dist[i]);
}

int main(void)
{
    freopen("butter.in", "r", stdin);
    freopen("butter.out", "w", stdout);

    scanf("%d %d %d", &n, &p, &c);
    int num;
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        cownum[num]++;
    }
    
    for (int i = 1; i <= p; i++)
        for (int j = 1; j <= p; j++)
            connect[i][j] = 10e8;
    for (int i = 1; i <= p; i++)
        connect[i][i] = 0;

    int p1, p2, val;
    for (int x = 0; x < c; x++) {
        scanf("%d %d %d", &p1, &p2, &val);
        connect[p1][p2] = val;
        connect[p2][p1] = val;
    }

    floyd();
    calc_dist();
    find_shortest_dist();

    printf("%lld\n", ans);
    return 0;
}