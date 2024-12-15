//Number of sides = Number of corners, hence we just need to count corners

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const int DIRS = 4;
const int d_i[DIRS] = {-1, 0, 1, 0};
const int d_j[DIRS] = {0, 1, 0, -1};

int N, M;
vector<vector<int>> grid;
vector<vector<bool>> visited;
vector<vector<bool>> completed;

int area = 0, perimeter = 0;

bool inside(int i, int j)
{
    return i >= 0 && i < N && j >= 0 && j < M;
}

void dfs(int i, int j)
{
    if (visited[i][j]) { 
        // We came through some edge that is not in the perimeter
        return;
    }

    area++;
    visited[i][j] = true;

    int prv = 1;
    for (int d = 0; d < DIRS + 1; d++) {
        int n_i = i + d_i[d % DIRS];
        int n_j = j + d_j[d % DIRS];

        int cur = inside(n_i, n_j) && grid[n_i][n_j] == grid[i][j];
        if (cur) {
            dfs(n_i, n_j);
            if (prv && d) {
                int s_i = i + d_i[d % DIRS] + d_i[d - 1];
                int s_j = j + d_j[d % DIRS] + d_j[d - 1];

                if (!(inside(s_i, s_j) && grid[s_i][s_j] == grid[i][j])) {
                    perimeter++;
                }
            }
        }
        else if (!prv) {
            perimeter++;
        }

        prv = cur;
    }

    completed[i][j] = true;
}

int main(void)
{
    freopen("fence.in", "r", stdin);
    freopen("fence.out", "w", stdout);

    int c;
    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);

        grid.pb({});
        while ((c = getchar()) != '\n') {
            grid.back().pb(c - 'A');
        }
    }

    N = grid.size();
    M = grid[0].size();

    visited.assign(N, vector<bool>(M, false));
    completed.assign(N, vector<bool>(M, false));
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!visited[i][j]) {
                area = perimeter = 0;
                dfs(i, j);

                ans += (ll)area * perimeter;
            }
        }
    }

    printf("%lld\n", ans);

    return 0;
}