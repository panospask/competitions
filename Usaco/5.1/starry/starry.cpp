/*
ID: panos.p1
LANG: C++11
TASK: starry
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXH 100
#define MAXW 100
#define MAXC 500

using namespace std;

typedef pair<int, int> ii;

bool visited[MAXH][MAXW];
bool visited2[MAXH][MAXW];
int h, w;
int sky[MAXH][MAXW];
int numassign[MAXH][MAXW];
int curc = 0;
int dirx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
int diry[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
int posVal[8] = { 1, 2, 4, 8, 4, 2, 1, 8 };
int ans[MAXH][MAXW];

map<int, int> RotateCluster[4];

void visit(int x, int y)
{
    if (visited[x][y])
        return;
    visited[x][y] = true;
    int val[8];
    for (int i = 0; i < 8; i++)
        val[i] = 0;
    
    int x1, y1;
    for (int i = 0; i < 8; i++) {
        x1 = x + dirx[i];
        y1 = y + diry[i];

        if (x1 < 0 || x1 >= w || y1 < 0 || y1 >= h)
            continue;
        if (sky[x1][y1] == 0)
            continue;

        for (int j = 0; j < 4; j++)
            val[j] += posVal[(i + 2 * j) % 8];
        visit(x1, y1);        
    }

    for (int j = 0; j < 4; j++)
        RotateCluster[j][val[j]]++;
}

void assign(int x, int y, char c)
{
    if (visited2[x][y])
        return;

    visited2[x][y] = true;
    ans[x][y] = c;
    int x1, y1;
    for (int i = 0; i < 8; i++) {
        x1 = x + dirx[i];
        y1 = y + diry[i];

        if (x1 < 0 || x1 >= w || y1 < 0 || y1 >= h)
            continue;
        if (sky[x1][y1] == 0)
            continue;

        assign(x1, y1, c);
    }
}

int main(void)
{
    freopen("starry.in", "r", stdin);
    freopen("starry.out", "w", stdout);

    scanf("%d %d", &h, &w);

    memset(visited, false, sizeof(visited));
    memset(visited2, false, sizeof(visited2));

    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++) {
            scanf("%1d", &sky[i][j]);
            ans[i][j] = '0';
        }

    map<map<int, int>, char> clusters;
    char curcar = 'a';
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++) {
            if (sky[i][j] && !visited[i][j]) {
                for (int x = 0; x < 4; x++)
                    RotateCluster[x].clear();

                visit(i, j);
                map<int, int> cluster = RotateCluster[0];
                if (clusters.count(cluster) == 0) {
                    for (int x = 0; x < 4; x++)
                        clusters[RotateCluster[x]] = curcar;
                    curcar++;
                }

                assign(i, j, clusters[RotateCluster[0]]);
            }
        }

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++)
            printf("%c", ans[i][j]);
        printf("\n");
    }
    return 0;
}