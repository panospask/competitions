#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M, K;
vector<vector<int>> grid;
vector<vector<int>> center;
vector<vector<int>> pref;

// Check the rectangle [i, j] --> [r, l]
bool good(int i, int j, int r, int l) {
    if (i == r || j == l) {
        return false;
    }

    // Check the inside square for enough centers
    return (pref[r - 1][l - 1] - pref[r - 1][j] - pref[i][l - 1] + pref[i][j]) >= K;
}

int main(void) {
    scanf("%d %d %d", &N, &M, &K);

    grid.resize(N + 2, vector<int>(M + 2, 0));
    center.resize(N + 2, vector<int>(M + 2, 0));
    pref.resize(N + 2, vector<int>(M + 2, 0));

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%1d", &grid[i][j]);
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (grid[i][j] && grid[i - 1][j] && grid[i][j - 1] && grid[i + 1][j] && grid[i][j + 1]) {
                center[i][j] = 1;
            }

            pref[i][j] = center[i][j] + pref[i][j - 1] + pref[i - 1][j] - pref[i - 1][j - 1];
        }
    }

    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            int l = M;
            for (int r = i + 1; r <= N; r++) {
                while (good(i, j, r, l)) {
                    l--;
                }
                ans += (M - l);
            }
        }
    }

    printf("%lld\n", ans);
}