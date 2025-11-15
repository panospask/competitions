#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

int N;
vector<pi> dominoes;
map<pi, int> idx;

vector<vector<bool>> dp;
vector<int> sos;

void precalculate(void) {
    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j < 7; j++) {
            dominoes.push_back({i, j});
            idx[{i, j}] = dominoes.size() - 1;
        }
    }
    N = 21;

    dp.assign(7, vector<bool>(1 << N, false));
    sos.assign(1 << N, 0);
    for (int i = 0; i < 7; i++) {
        dp[i][0] = true;
    }

    int ans = 0;
    for (int mask = 0; mask < (1 << N); mask++) {
        bool check = false;
        for (int v = 0; v < 7; v++) {
            check = check || dp[v][mask];
        }
        sos[mask] = check;

        for (int i = 0; i < N; i++) {
            if (CHECK_BIT(mask, i)) {
                continue;
            }

            if (dp[dominoes[i].first][mask]) {
                dp[dominoes[i].second][mask | (1 << i)] = true;
            }
            if (dp[dominoes[i].second][mask]) {
                dp[dominoes[i].first][mask | (1 << i)] = true;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int mask = 0; mask < (1 << N); mask++) {
            if (CHECK_BIT(mask, i)) {
                sos[mask] += sos[mask ^ (1 << i)];
            }
        }
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    precalculate();
    while (t--) {
        int N;
        scanf("%d", &N);

        int mask = 0;
        for (int i = 0; i < N; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            x--; y--;

            mask = mask | (1 << idx[{x, y}]);

        }
        printf("%d\n", sos[mask] - 1);
    }
}