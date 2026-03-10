#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M;
vector<vector<ll>> cost;
vector<vector<bool>> l;
vector<vector<bool>> up;
vector<vector<bool>> visited;
vector<vector<bool>> use;

ll total = 0;
bool usable = false;

bool inside(int i, int j) {
    return 0 <= i && i < N - 1 && 0 <= j && j < M - 1;
}

void dfs(int i, int j) {
    if (visited[i][j]) {
        return;
    }

    visited[i][j] = true;
    usable = usable && use[i][j];
    total += cost[i][j];

    if (inside(i - 1, j) && up[i][j] == false) {
        dfs(i - 1, j);
    }
    if (inside(i, j - 1) && l[i][j] == false) {
        dfs(i, j - 1);
    }
    if (inside(i + 1, j) && up[i + 1][j] == false) {
        dfs(i + 1, j);
    }
    if (inside(i, j + 1) && l[i][j + 1] == false) {
        dfs(i, j + 1);
    }
}

void solve(void) {
    scanf("%d %d", &N, &M);

    cost.assign(N - 1, vector<ll>(M - 1, 0));
    l.assign(N - 1, vector<bool>(M - 1, true));
    up.assign(N - 1, vector<bool>(M - 1, true));
    visited.assign(N - 1, vector<bool>(M - 1, false));
    use.assign(N - 1, vector<bool>(M - 1, true));


    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < M; j++) {
            int x;
            scanf("%d", &x);

            if (inside(i, j)) {
                cost[i][j] += x;
            }
            if (inside(i, j - 1)) {
                cost[i][j - 1] -= x;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M - 1; j++) {
            int x;
            scanf("%d", &x);

            if (inside(i, j)) {
                cost[i][j] += x;
            }
            if (inside(i - 1, j)) {
                cost[i - 1][j] -= x;
            }
        }
    }
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < M; j++) {
            int x;
            scanf("%1d", &x);

            if (x == 0) {
                if (!inside(i, j - 1)) {
                    use[i][j] = false;
                }
                else if (!inside(i, j)) {
                    use[i][j - 1] = false;
                }
                else {
                    l[i][j] = false;
                }
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M - 1; j++) {
            int x;
            scanf("%1d", &x);

            if (x == 0) {
                if (!inside(i - 1, j)) {
                    use[i][j] = false;
                }
                else if (!inside(i, j)) {
                    use[i - 1][j] = false;
                }
                else {
                    up[i][j] = false;
                }
            }
        }
    }


    ll ans = 0;
    for (int i = N - 2; i >= 0; i--) {
        for (int j = M - 2; j >= 0; j--) {
            if (!visited[i][j]) {
                total = 0;
                usable = true;
                dfs(i, j);
                ans += max(0LL, usable * total);
            }
        }
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}