#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

bool been_in_state[25][25][20000];
bool can_go[25][25];
char maze[25][25];
int n;

int dir_ver[4] = {1, 0, -1, 0};
int dir_hor[4] = {0, 1, 0, -1};

map<ii, pair<ii, int>> moves;

int threepow[10];

set<int> answers;

bool check_state(int b)
{
    int grid[3][3]; // 0 for nothing, 1 for M, 2 for O
    for (int i = 0; i < 3; i++)
        for (int j =  0; j < 3; j++) {
            grid[i][j] = b % 3;
            b /= 3;
        }
            

    bool isgood = false;
    for (int i = 0; i < 3; i++) {
        if ((grid[i][0] == 1 && grid[i][1] == 2 && grid[i][2] == 2)
        || grid[i][0] == 2 && grid[i][1] == 2 && grid[i][2] == 1)
            isgood = true;
    }
    for (int j = 0; j < 3; j++) {
        if ((grid[0][j] == 1 && grid[1][j] == 2 && grid[2][j] == 2)
        || grid[0][j] == 2 && grid[1][j] == 2 && grid[2][j] == 1)
            isgood = true;
    }

    if (grid[0][0] == 1 && grid[1][1] == 2 && grid[2][2] == 2) isgood = true;
    if (grid[0][0] == 2 && grid[1][1] == 2 && grid[2][2] == 1) isgood = true;
    if (grid[0][2] == 1 && grid[1][1] == 2 && grid[2][0] == 2) isgood = true;
    if (grid[0][2] == 2 && grid[1][1] == 2 && grid[2][0] == 1) isgood = true;

    return isgood;
}

void dfs(int i, int j, int b)
{
    if (!can_go[i][j] || been_in_state[i][j][b])
        return;

    been_in_state[i][j][b] = true;
    if (moves.count(mp(i,j))) {
        int x, y;
        tie(x, y) = moves[mp(i,j)].first;
        int indx = threepow[(3*x + y)];

        if ((b / indx) % 3 == 0) {
            b += indx * moves[mp(i,j)].second;

            if (been_in_state[i][j][b]) return;

            been_in_state[i][j][b] = true;
            if (check_state(b)) {
                answers.insert(b);
                return;
            }
        }
    }

    for (int x = 0; x < 4; x++)
        dfs(i + dir_ver[x], j + dir_hor[x], b);
}

int main(void)
{
    // freopen("mazetactoe.in", "r", stdin);
    // freopen("mazetactoe.out", "w", stdout);

    scanf("%d", &n);
    string cur;
    cur.resize(3);
    ii bessiepos;

    threepow[0] = 1;
    for (int i = 1; i <= 9; i++)
        threepow[i] = threepow[i-1] * 3;

    for (int i = 0; i < n; i++) {
        getchar();
        for (int j = 0; j < n; j++) {
            cur[0] = getchar();
            cur[1] = getchar();
            cur[2] = getchar();

            if (cur[0] == '#')
                can_go[i][j] = false;
            else {
                can_go[i][j] = true;
                if (cur[0] == 'B')
                    bessiepos = mp(i,j);
                else if (cur[0] == 'M' || cur[0] == 'O') {
                    int id = (cur[0] == 'O') + 1;
                    int x = cur[1] - '1';
                    int y = cur[2] - '1';

                    moves[mp(i,j)] = mp(mp(x,y), id);
                }
            }
        }
    }

    dfs(bessiepos.first, bessiepos.second, 0);

    printf("%d\n", (int)answers.size());
    return 0;
}