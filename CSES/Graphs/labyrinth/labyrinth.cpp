#include <bits/stdc++.h>
#define MAXN 1000
#define MAXM 1000

using namespace std;

typedef pair<int, int> ii;

int n, m;
ii start;
ii fin;

int grid[MAXN + 2][MAXM + 2];
int dist[MAXN + 2][MAXM + 2];
char par_dir[MAXN + 2][MAXM + 2];
ii par[MAXN + 2][MAXM + 2];
bool visited[MAXN + 2][MAXM + 2];

char dir_par[4] = {'D', 'R', 'U', 'L'};
int dir_hor[4] = {0, 1, 0, -1};
int dir_ver[4] = {1, 0, -1, 0};

bool isgood(ii a)
{
    if (a.first < 0 || a.first >= n)
        return false;
    if (a.second < 0 || a.second >= m)
        return false;

    if (grid[a.first][a.second] == 0)
        return false;

    return true;
}

int bfs(void)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dist[i][j] = INT_MAX;

    queue<ii> q;
    dist[start.first][start.second] = 0;
    visited[start.first][start.second] = true;
    par[start.first][start.second] = make_pair(-1,-1);
    q.push(start);

    while (!q.empty()) {
        ii node = q.front(); q.pop();
        
        if (node == fin)
            break;

        for (int x = 0; x < 4; x++) {
            ii neigh;
            neigh.first = node.first + dir_ver[x];
            neigh.second = node.second + dir_hor[x];    

            if (isgood(neigh) && !visited[neigh.first][neigh.second]) {
                dist[neigh.first][neigh.second] = dist[node.first][node.second] + 1;
                visited[neigh.first][neigh.second] = true;
                par_dir[neigh.first][neigh.second] = dir_par[x];
                par[neigh.first][neigh.second] = node;
                q.push(neigh);
            }
        }
    }

    return dist[fin.first][fin.second];
}

int main(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        getchar();
        for (int j = 0; j < m; j++) {
            char c = getchar();
            if (c == '#') {
                grid[i][j] = 0;
            }
            else {
                grid[i][j] = 1;
                if (c == 'A')
                    start = make_pair(i, j);
                else if (c == 'B')
                    fin = make_pair(i, j);
            }
        }
    }

    int ans = bfs();
    if (ans == INT_MAX) {
        printf("NO\n");
    }
    else {
        printf("YES\n%d\n", ans);
        vector<char> anspath;
        
        ii node = fin;
        while (par[node.first][node.second].first != -1) {
            anspath.push_back(par_dir[node.first][node.second]);
            node = par[node.first][node.second];
        }

        reverse(anspath.begin(), anspath.end());
        for (auto c : anspath)
            printf("%c", c);
        printf("\n");
    }

    return 0;
}