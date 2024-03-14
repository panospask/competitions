#include <bits/stdc++.h>
#define MAXN 25000
#define MAXM 25000

using namespace std;

typedef pair<int, int> ii;

int n, m;
ii cur_square;
ii cur_dir;
ii goal_square;

map<ii, int> visited;

ii find_next_bounce(void)
{
    int x_time = 0;
    if (cur_dir.first == 1) {
        x_time = abs(n - 1 - cur_square.first);
    }
    else 
        x_time = abs(0 - cur_square.first);

    int y_time = 0;
    if (cur_dir.second == 1)
        y_time = abs(m - 1 - cur_square.second);
    else 
        y_time = abs(0 - cur_square.second);

    int mintime = min(x_time, y_time);
    ii new_square = make_pair(cur_square.first + mintime * cur_dir.first, cur_square.second + mintime * cur_dir.second);

    return new_square;
}

void solve(void)
{
    visited.clear();

    scanf("%d %d", &n, &m);
    scanf("%d %d", &cur_square.first, &cur_square.second);
    scanf("%d %d", &goal_square.first, &goal_square.second);

    cur_square.first--; cur_square.second--;
    goal_square.first--; goal_square.second--;

    getchar();
    char idir = getchar();
    char jdir = getchar();

    if (idir == 'U')
        cur_dir.first = -1;
    else 
        cur_dir.first = 1;
    if (jdir == 'R')
        cur_dir.second = 1;
    else 
        cur_dir.second = - 1;

    int bounces = 0;
    visited[cur_square]++;

    bool still_going = true;
    bool found = false;
    while (still_going) {
        ii next_square = find_next_bounce();

        int x_dist = cur_dir.first * (goal_square.first - cur_square.first);
        int y_dist = cur_dir.second * (goal_square.second - cur_square.second);
        if (x_dist >= 0 && x_dist == y_dist) {
                found = true;
                break;
            }

        bounces++;
        visited[next_square]++;
        if (visited[next_square] > 2) {
            still_going = false;
            break;
        }

        // Recalculate direction
        if (cur_dir.first == 1) {
            if (next_square.first == n - 1)
                cur_dir.first = -1;
        }
        else {
            if (next_square.first == 0)
                cur_dir.first = 1;
        }   

        if (cur_dir.second == 1) {
            if (next_square.second == m - 1)
                cur_dir.second = -1;
        }
        else {
            if (next_square.second == 0)
                cur_dir.second = 1;
        }

        cur_square = next_square;
    }

    if (found)
        printf("%d\n", bounces);
    else 
        printf("-1\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
        solve();
}