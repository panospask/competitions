/*
ID: panos.p1
LANG: C++11
TASK: ttwo
*/

#include <bits/stdc++.h>
#define mp make_pair

#define MAXN 10

using namespace std;

typedef pair<int, int> ii;

int cows[10000], john[10000];
char field[MAXN][MAXN];
bool done = false;

map<pair<ii, ii>, vector<pair<ii,ii>>> visits;

ii j_dir, c_dir;
ii j_cord, c_cord;
int minutes = 0;
int ans = 0;

void rotate_clockwise(ii& dir)
{
    if (dir.second == 0) {
        dir.second = -1 * dir.first;
        dir.first = 0;
    }
    else {
        dir.first = dir.second;
        dir.second = 0;
    }
}

ii operator + (ii a, ii b)
{
    a.first += b.first;
    a.second += b.second;

    return a;
}

ii operator - (ii a, ii b)
{
    a.first -= b.first;
    a.second -= b.second;

    return a;
}

bool check_limits(ii a)
{
    if (a.first < 0 || a.first >= MAXN)
        return false;
    if (a.second < 0 || a.second >= MAXN)
        return false;

    return true;
}

bool find_in(const pair<ii, ii> a, vector<pair<ii,ii>>& dirs)
{
    for (auto& b : dirs) {
        if (a == b)
            return true;
    }

    return false;
}

void sim_minute(void)
{
    minutes++;

    // John
    j_cord = j_cord + j_dir;
    if (!check_limits(j_cord) || field[j_cord.first][j_cord.second] == '*') {
        j_cord = j_cord - j_dir;
        rotate_clockwise(j_dir);
    }

    //Cows
    c_cord = c_cord + c_dir;
    if (!check_limits(c_cord) || field[c_cord.first][c_cord.second] == '*') {
        c_cord = c_cord - c_dir;
        rotate_clockwise(c_dir);
    }

    if (j_cord == c_cord) {
        done = true;
        ans = minutes;
        return;
    }

    else if (find_in(mp(j_dir, c_dir) ,visits[mp(j_cord, c_cord)])) {
        done = true;
        ans = 0;
        // printf("Iteration: %d. Values: %d %d\n", minutes, j_cord.first, j_cord.second);
        return;
    }
    else 
        visits[mp(j_cord, c_cord)].push_back(mp(j_dir, c_dir));
}

int main(void)
{
    freopen("ttwo.in", "r", stdin);
    freopen("ttwo.out", "w", stdout);

    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            field[i][j] = getchar();
            if (field[i][j] == 'C') 
                c_cord = mp(i, j);
            else if (field[i][j] == 'F')
                j_cord = mp(i, j);
        }
        getchar();
    }

    c_dir = mp(-1, 0);
    j_dir = mp(-1, 0);

    visits[mp(j_cord, c_cord)].push_back(mp(j_dir, c_dir));

    while (!done)
        sim_minute();

    printf("%d\n", ans);
    return 0;
}