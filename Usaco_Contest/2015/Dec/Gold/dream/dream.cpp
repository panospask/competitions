#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;

const int MAXN = 1000;
const int DIRS = 4;
const int RED = 0, PINK = 1, ORANGE = 2 , BLUE = 3, PURPLE = 4;

int dir_v[] = {1, 0, -1, 0};
int dir_h[] = {0, 1, 0, -1};

struct Situation {
    int i, j;
    bool smell;
    int dir;
};

// dist for i, j, smell, direction
int n, m;
int dist[MAXN][MAXN][2][DIRS];
int grid[MAXN][MAXN];
Situation initial;
pi dest;

bool inbound(int i, int j)
{
    return i >= 0 && j >= 0 && i < n && j < m;
}

bool goodsquare(int i, int j, int smell)
{
    if (!inbound(i, j))
        return false;

    if (grid[i][j] == RED)
        return false;

    if (grid[i][j] == BLUE && !smell)
        return false;

    return true;
}

int main(void)
{
    freopen("dream.in", "r", stdin);
    freopen("dream.out", "w", stdout);

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
            for (int smell = 0; smell < 2; smell++)
                for (int d = 0; d < DIRS; d++)
                    dist[i][j][smell][d] = INT_MAX;
        }


    deque<Situation> q;
    initial = {0, 0, false, 0};
    dist[0][0][0][0] = 0;
    q.push_front(initial);
    dest = mp(n - 1, m - 1);

    int ans = -1;
    while (!q.empty()) {

        Situation cur = q.front();
        q.pop_front();

        int i, j;
        tie(i, j) = mp(cur.i, cur.j);

        int curd = dist[cur.i][cur.j][cur.smell][cur.dir];

        if (i == dest.f && j == dest.s) {
            ans = dist[cur.i][cur.j][cur.smell][cur.dir];
            break;
        }

        bool smell = cur.smell;
        if (grid[i][j] == PURPLE)
            smell = false;
        if (grid[i][j] == ORANGE)
            smell = true;

        // Advance forwards
        bool advance = false;
        int ni = i + dir_v[cur.dir];
        int nj = j + dir_h[cur.dir];
        if (goodsquare(ni, nj, smell)) {
            if (dist[ni][nj][smell][cur.dir] > curd + 1) {
                dist[ni][nj][smell][cur.dir] = curd + 1;
                q.push_back({ni, nj, smell, cur.dir});
            }
            advance = true;
        }

        if (grid[i][j] != PURPLE || !advance) {
            // Turn
            for (int d = cur.dir + 1; d % DIRS != cur.dir; d++) {
                d %= DIRS;
                if (dist[i][j][smell][d] > curd) {
                    dist[i][j][smell][d] = curd;
                    q.push_front({i, j, smell, d});
                }
            }
        }

    }

    printf("%d\n", ans);
}