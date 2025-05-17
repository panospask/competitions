#include <bits/stdc++.h>

using namespace std;

int N;

vector<vector<int>> grid;

void solve(void) {
    scanf("%d", &N);

    grid.assign(N, vector<int>(N));

    int num = 1;
    int i = (N + 1) / 2 - 1;
    int j = (N + 1) / 2 - 1;
    grid[i][j] = 0;
    int dir = 0;

    int i_s = i, i_l = i;
    int j_s = j, j_l = j;

    while (num < N * N) {
        if (dir == 0) {
            i++;
        }
        else if (dir == 1) {
            j++;
        }
        else if (dir == 2) {
            i--;
        }
        else if (dir == 3) {
            j--;
        }

        grid[i][j] = num++;

        if (i < i_s || i > i_l || j < j_s || j > j_l) {
            dir = (dir + 1) % 4;
        }
        i_s = min(i_s, i);
        j_s = min(j_s, j);
        i_l = max(i_l, i);
        j_l = max(j_l, j);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", grid[i][j]);
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