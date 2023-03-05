#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000

using namespace std;

typedef pair<int, int> ii;

int n;

map<ii, bool> can_go[4];
int u = 0, l = 1, d = 2, r = 3;
int dir_ver[4] = {1, 0, -1, 0};
int dir_hor[4] = {0, -1, 0, 1};
map<ii, bool> visited;
map<ii, bool> is_reached[4];
int upmost = 0, leftmost = 0, rightmost = 0, downmost = 0;

int floodfill(ii start)
{
    stack<ii> tiles;
    tiles.push(start);

    int cur_comp = 1;
    int i, j;
    while (!tiles.empty()) {
        tie(i, j) = tiles.top();
        tiles.pop();
        if (i < downmost || i > upmost || j < leftmost || j > rightmost)
            continue;

        if (visited[mp(i, j)]) {
            // Reaching an already visited square implies we have a new component

            // Though we must check if we backtracked 
            cur_comp++;
            continue;
        }

        visited[mp(i, j)] = true;
        for (int x = 0; x < 4; x++)
            if (can_go[x].count(mp(i,j)) && !is_reached[(x+2)%4].count(mp(i,j))) {
                tiles.push(mp(i + dir_ver[x], j + dir_hor[x]));
                is_reached[x][mp(i + dir_ver[x], j + dir_hor[x])] = true;
            }

    }

    return cur_comp;
}

int main(void)
{
    freopen("gates.in", "r", stdin);
    freopen("gates.out", "w", stdout);

    scanf("%d", &n);
    char c;
    getchar();

    ii cur_pos = mp(0, 0);

    for (int i = 0; i < n; i++) {
        c = getchar();
        if (c == 'N') {
            can_go[u][cur_pos] = true;
            cur_pos = mp(cur_pos.first + 1, cur_pos.second);
            can_go[d][cur_pos] = true;

            upmost = max(upmost, cur_pos.first);
        }
        else if (c == 'S') {
            can_go[d][cur_pos] = true;
            cur_pos = mp(cur_pos.first - 1, cur_pos.second);
            can_go[u][cur_pos] = true;

            downmost = min(downmost, cur_pos.first);
        }
        else if (c == 'W') {
            can_go[l][cur_pos] = true;
            cur_pos = mp(cur_pos.first, cur_pos.second - 1);
            can_go[r][cur_pos] = true;

            leftmost = min(leftmost, cur_pos.second);
        }
        else {
            can_go[r][cur_pos] = true;
            cur_pos = mp(cur_pos.first, cur_pos.second + 1);
            can_go[l][cur_pos] = true;

            rightmost = max(rightmost, cur_pos.first);
        }

    }

    int components = floodfill(mp(0,0));

    printf("%d\n", components - 1);
    return 0;
}