#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 25

using namespace std;

typedef pair<int, int> ii;

int visited[MAXN + 2][MAXN + 2];
char board[3][3];
map<ii, pair<char,ii>> move_make;
bool can_go[MAXN + 2][MAXN + 2];
map<string[3], bool> reached;
ii bessiepos;
int latest_piece = -1;
int cur_step;
vector<ii> movesquares;
map<ii, int> square_to_num;

int dir_ver[4] = {1, 0, -1, 0};
int dir_hor[4] = {0, 1, 0, -1};

set<vector<string>> answers;

int n;

bool check_string(string& s)
{
    if (s == "MOO" || s == "OOM")
        return true;
    return false;
}

bool check_using(int i, int j)
{
    // Check horizontal
    string cur;
    for (int x = 0; x < 3; x++)
        cur.push_back(board[i][x]);
    
    if (check_string)
        return true;

    // Check vertical
    for (int x = 0; x < 3; x++)
        cur.push_back(board[x][j]);
    
    if (check_string)
        return true;

    // Check diagonal
    if (i == j) {
        for (int x = 0; x < 3; x++)
            cur.push_back(board[x][x]);
        if (check_string)
            return true;
    }
    if (i == 3 - j - 1) {
        for (int x = 0; x < 3; x++)
            cur.push_back(board[x][2-x]);
        if (check_string)
            return true;
    }

    return false;
}

void make_floor(int i, int j)
{
    can_go[i][j] = true;
}

void make_move(int i, int j, string& m)
{
    make_floor(i,j);
    move_make[mp(i,j)] = mp(m[0], mp(m[1]-'1',m[2]-'1'));
}

void make_wall(int i, int j)
{
    can_go[i][j] = false;
}

void dfs(int i, int j)
{
    if (visited[i][j] > 3)
        return;
    
    visited[i][j]++;

    
}

int main(void)
{
    freopen("mazetactoe.in", "r", stdin);
    freopen("mazetactoe.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin >> n;
    string cur;
    cur.resize(3);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            for (int x = 0; x < 3; x++)
                cin >> cur[x];
            
            if (cur[0] == '#')
                make_wall(i,j);
            else if (cur[0] == '.')
                make_floor(i,j);
            else if (cur[0] == 'B') {
                bessiepos = mp(i,j);
                make_floor(i, j);
            }
            else {
                make_move(i, j, cur);
                movesquares.pb(mp(i,j));
                square_to_num[mp(i,j)] = movesquares.size() - 1;
            }
        }
}