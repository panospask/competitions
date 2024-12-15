#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int SOURCE = 9;
const int TARGET = 0;

const int DIRS = 4;
const int d_i[DIRS] = {1, 0, -1, 0};
const int d_j[DIRS] = {0, 1, 0, -1};

int N, M;
ll ans = 0;
vector<vector<int>> grid;
vector<vector<ll>> cnt;
vector<vector<bool>> visited;

bool inside(int i, int j)
{
    return i >= 0 && i < N && j >= 0 && j < M;
}

void bfs(void)
{
    queue<pi> q;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == SOURCE) {
                cnt[i][j] = 1;
                q.push(mp(i, j));
            }
        }
    }

    while (!q.empty()) {
        int i, j;
        tie(i, j) = q.front();
        q.pop();

        if (grid[i][j] == TARGET) {
            ans += cnt[i][j];
        }

        for (int d = 0; d < DIRS; d++) {
            int n_i = i + d_i[d];
            int n_j = j + d_j[d];

            if (inside(n_i, n_j) && grid[n_i][n_j] + 1 == grid[i][j]) {
                cnt[n_i][n_j] += cnt[i][j];

                if (!visited[n_i][n_j]) {
                    visited[n_i][n_j] = true;
                    q.push(mp(n_i, n_j));
                }
            }
        }
    }
}

int main(void)
{
    freopen("trails.in", "r", stdin);
    freopen("trails.out", "w", stdout);

    int c = 0;
    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);

        grid.pb({});
        while ((c = getchar()) != '\n') {
            grid.back().pb(c - '0');
        }
    }

    N = grid.size();
    M = grid[0].size();

    cnt.assign(N, vector<ll>(M, 0));
    visited.assign(N, vector<bool>(M, false));

    bfs();

    printf("%lld\n", ans);

    return 0;
}