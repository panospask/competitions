#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int DIRS = 4;
const int d_i[DIRS] = {1, 0, -1, 0};
const int d_j[DIRS] = {0, -1, 0, 1}; 

typedef pair<int, int> pi;

int N, M;
vector<vector<int>> grid;
vector<vector<vector<bool>>> visited;
vector<vector<bool>> path;

bool outside(int i, int j)
{
    return i < 0 || i >= N || j < 0 || j >= M;
}

bool blocked(int i, int j)
{
    return grid[i][j];
}

bool looped(int i, int j, int d, int s)
{
    if (visited[i][j][d]) {
        return true;
    }

    if (s) {
        path[i][j] = true;
    }

    visited[i][j][d] = true;

    int n_i = i + d_i[d];
    int n_j = j + d_j[d];

    bool res = false;

    if (outside(n_i, n_j)) {
        res =  false;
    }
    else if (blocked(n_i, n_j)) {
        res = looped(i, j, (d + 1) % DIRS, s);
    }
    else {
        res = looped(n_i, n_j, d, s);
    }

    visited[i][j][d] = false;

    return res;
}

int main(void)
{
    freopen("guard.in", "r", stdin);
    freopen("guard.out", "w", stdout);

    int c = 0;

    int i = 0, j = 0;
    int s_i, s_j, s_d;
    while (c != EOF) {
        j = 0;
        grid.pb({});
        while ((c = getchar()) != '\n' && c != EOF) {
            grid.back().pb(c == '#');

            if (c != '.' && c != '#') {
                s_i = i;
                s_j = j;

                if (c == '^') {
                    s_d = 3;
                }
                else if (c == '>') {
                    s_d = 4;
                }
                else if (c == '<') {
                    s_d = 2;
                }
                else {
                    s_d = 1;
                }
                s_d--;
            }  

            j++; 
        }

        i++;
    }

    N = grid.size();
    M = grid[0].size();

    visited.assign(N, vector<vector<bool>>(M, vector<bool>(DIRS, false)));
    path.resize(N, vector<bool>(M, false));
    looped(s_i, s_j, s_d, true);

    int ans = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (path[i][j] && (s_i != i || s_j != j)) {
                grid[i][j] = 1;

                if (looped(s_i, s_j, s_d, false)) {
                    ans++;
                }

                grid[i][j] = 0;
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}