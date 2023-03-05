#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;

typedef pair<int, int> ii;

int n, m;
bool islit[MAXN + 5][MAXN + 5];
bool reached[MAXN + 5][MAXN + 5];
bool done_with[MAXN + 5][MAXN + 5];
vector<ii> switches[MAXN + 5][MAXN + 5];
int dir_ver[4] = {-1, 0, 1, 0};
int dir_hor[4] = {0, -1, 0, 1};
int illuminate;

int dfs(int i, int j)
{
    if (i < 0 || i >= n || j < 0 || j >= n) 
        return 0;
    
    reached[i][j] = true;
    if (!islit[i][j] || done_with[i][j])
        return 0;

    done_with[i][j] = true;
    int cur_vis = 1;

    for (auto& room : switches[i][j]) 
        if (!islit[room.first][room.second]) {
            illuminate++;
            islit[room.first][room.second] = true;
            if (reached[room.first][room.second])
                cur_vis += dfs(room.first, room.second);
        }

    for (int x = 0; x < 4; x++) 
        cur_vis += dfs(i + dir_ver[x], j + dir_hor[x]);

    return cur_vis;
}

int main(void)
{
    freopen("lightson.in", "r", stdin);
    freopen("lightson.out", "w", stdout);

    scanf("%d %d", &n, &m);
    int x, y, a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &x, &y, &a, &b);
        x--; y--; a--; b--;
        switches[x][y].pb(mp(a,b));
    }

    islit[0][0] = true;
    illuminate = 1;
    int ans = dfs(0, 0);

    printf("%d\n", illuminate);
    return 0;
}