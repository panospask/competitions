#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int INF = 1e6;

struct Queries {
    int j1, j2, v;
};

int N, M;

vector<vector<int>> grid;

vector<vector<int>> last;
vector<vector<vector<Queries>>> q;

vector<vector<int>> res;

void solve(void) {
    scanf("%d %d", &N, &M);

    res.assign(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%1d", &res[i][j]);
        }
    }

    bool s = false;
    if (N > M) {
        s = true;
        swap(N, M);
    }

    grid.assign(N, vector<int>(M));
    q.assign(N, vector<vector<Queries>>(M, vector<Queries>()));
    last.assign(M, vector<int>(M, -1));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!s) {
                grid[i][j] = res[i][j];
            }
            else {
                grid[i][j] = res[j][i];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j1 = 0; j1 < M; j1++) {
            for (int j2 = j1 + 1; j2 < M; j2++) {
                if (grid[i][j1] && grid[i][j2]) {
                    if (last[j1][j2] != -1) {
                        int v = (j2 - j1 + 1) * (i - last[j1][j2] + 1);

                        for (int k = last[j1][j2]; k <= i; k++) {
                            q[k][j1].pb({j1, j2, v});
                        }
                    }

                    last[j1][j2] = i;
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ;
        }
    }

    if (s) {
        swap(N, M);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}