#include <bits/stdc++.h>
#define MAXH 4000
#define MAXW 4000

using namespace std;

typedef pair<int, int> ii;

int n, h, w;
int meadow[MAXH + 2][MAXW + 2];
bool visited[MAXH + 2][MAXW + 2];
int dist[MAXH + 2][MAXW + 2];
int ans;

bool isanimal(ii a)
{
    return meadow[a.first][a.second] != 0;
}

int calcfunc(ii a, ii b)
{
    int type1 = meadow[a.first][a.second];
    int type2 = meadow[b.first][b.second];
    if ( type1 == 0 || type2 == 0)
        return 1e9;

    return !(type1 == type2); 
}

void mod_dijkstra(ii start)
{

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            dist[i][j] = 1e9;

    deque<ii> q;
    dist[start.first][start.second] = 1;
    q.push_front(start);

    while (!q.empty()) {
        ii node = q.front(); q.pop_front();
        if (visited[node.first][node.second])
            continue;

        visited[node.first][node.second] = true;
        ans = max(ans, dist[node.first][node.second]);
        ii neigh; 
        if (node.first > 0) {
            neigh = node;
            neigh.first--;
            if (isanimal(neigh)) {

                int d = calcfunc(node, neigh);
                if (dist[neigh.first][neigh.second] > d + dist[node.first][node.second]) {
                    dist[neigh.first][neigh.second] = d + dist[node.first][node.second];
                    if (d == 1)
                        q.push_back(neigh);
                    else 
                        q.push_front(neigh);
                }
            }
        }
        if (node.second > 0) {
            neigh = node;
            neigh.second--;
            if (isanimal(neigh)) {

                int d = calcfunc(node, neigh);
                if (dist[neigh.first][neigh.second] > d + dist[node.first][node.second]) {
                    dist[neigh.first][neigh.second] = d + dist[node.first][node.second];
                    if (d == 1)
                        q.push_back(neigh);
                    else 
                        q.push_front(neigh);
                }
            }
        }
        if (node.first < h - 1) {
            neigh = node;
            neigh.first++;
            if (isanimal(neigh)) {
                

                int d = calcfunc(node, neigh);
                if (dist[neigh.first][neigh.second] > d + dist[node.first][node.second]) {
                    dist[neigh.first][neigh.second] = d + dist[node.first][node.second];
                    if (d == 1)
                        q.push_back(neigh);
                    else 
                        q.push_front(neigh);
                }
            }
        }
        if (node.second < w - 1) {
            neigh = node;
            neigh.second++;
            if (isanimal(neigh)) {
                int d = calcfunc(node, neigh);
                if (dist[neigh.first][neigh.second] > d + dist[node.first][node.second]) {
                    dist[neigh.first][neigh.second] = d + dist[node.first][node.second];
                    if (d == 1)
                        q.push_back(neigh);
                    else 
                        q.push_front(neigh);
                }
            }
        }
    }
}

int main(void)
{
    scanf("%d %d", &h, &w);
    for (int i = 0; i < h; i++) {
        getchar();
        for (int j = 0; j < w; j++) {
            char c = getchar();
            if (c == '.')
                meadow[i][j] = 0;
            else if (c == 'R')
                meadow[i][j] = 1;
            else 
                meadow[i][j] = 2;
        }
    }

    mod_dijkstra(make_pair(0,0));

    printf("%d\n", ans);
    return 0;
}