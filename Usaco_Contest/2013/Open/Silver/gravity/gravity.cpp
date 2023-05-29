#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

struct state {
    int i, j;
    bool gravflip;
};
typedef struct state State;

typedef pair<int, int> pi;

const int DIRS = 2;
int d_h[] = {1, -1};

int n, m;
vector<vector<int>> flips[2];
vector<vector<int>> grid;
State initial;
pi destination;

bool inbound(int i, int j)
{
    return i >=0 && j >= 0 && i < n && j < m;
}

int main(void)
{
    freopen("gravity.in", "r", stdin);
    freopen("gravity.out", "w", stdout);

    scanf("%d %d", &n, &m);
    grid.resize(n, vector<int>(m));
    flips[0].assign(n, vector<int>(m, -1));
    flips[1].assign(n, vector<int>(m, -1));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            char c;
            scanf(" %c", &c);
            if (c == '#')
                grid[i][j] = 0;
            else {
                grid[i][j] = 1;
                if (c == 'C')
                    initial = {i, j, false};
                if (c == 'D')
                    destination = {i, j};
            }
        }

    deque<State> q;
    flips[0][initial.i][initial.j] = 0;
    q.push_back(initial);

    int ans = -1;
    while (!q.empty()) {
        int i, j;
        bool grav;

        State cur = q.front(); q.pop_front();
        i = cur.i;
        j = cur.j;
        grav = cur.gravflip;

        // assert(flips[grav][i][j] % 2 == grav);

        if (mp(i, j) == destination) {
            ans = flips[grav][i][j];
            break;
        }

        int nxti = grav ? i - 1 : i + 1;
        if (!inbound(nxti, j))
            continue;

        if (grid[nxti][j]) {
            if (flips[grav][nxti][j] == -1) {
                flips[grav][nxti][j] = flips[grav][i][j];
                q.push_front({nxti, j, grav});
            }
        }
        else {
            // Can move around!
            for (int x = 0; x < DIRS; x++) {
                int nxtj = j + d_h[x];
                if (inbound(i, nxtj) && grid[i][nxtj]) {
                    if (flips[grav][i][nxtj] == -1) {
                        flips[grav][i][nxtj] = flips[grav][i][j];
                        q.push_front({i, nxtj, grav});
                    }
                }
            }

            // Also try switching the gravity
            if (flips[!grav][i][j] == -1) {
                flips[!grav][i][j] = flips[grav][i][j] + 1;
                q.push_back({i, j, !grav});
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}