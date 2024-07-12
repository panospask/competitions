    /*This problem needs arrays instad of vectors due to
    extremely tight ML and TL*/
    /*I think this solution is O(N^4), there probably exists an optimization
    to make it O(N^3)*/

    #include <bits/stdc++.h>
    #define pb push_back
    #define MOD(var, M) (((var) >= (M)) ? ((var) - M) : (var))

    using namespace std;

    const int MAXN = 500;
    const int INF = 1e9;

    int N, K;
    bool stage[MAXN][MAXN];

    vector<int> adj_list[MAXN];
    // dp[l][r][k]:  Maximum number of stages if enclosed by l, r
    // and being in the stages such that l < s < r'
    // Where r' = l > r ? r = r + N : r

    // k == 0: Starting in l
    // k == 1: Starting in r
    int dp[MAXN][MAXN][2];

    // Before the intersection with the first stage
    // You can only choose one way to follow
    // Either from l to r or from r to l
    int bef[MAXN][MAXN][2];

    int main(void)
    {
        scanf("%d %d", &N, &K);

        for (int i = 0; i < N; i++) {
            int v;
            scanf("%d", &v);

            while (v != 0) {
                v--;
                stage[i][v] = true;
                adj_list[i].pb(v);
                adj_list[i].pb(v + N);
                scanf("%d", &v);
            }

            sort(adj_list[i].begin(), adj_list[i].end());
        }

        for (int len = 1; len <= N; len++) {
            for (int l = 0; l < N; l++) {
                int r_actual = l + len - 1;
                int r = MOD(r_actual, N);

                bef[l][r][0] = bef[l][r][1] = -INF;

                for (int i_actual = l + 1; i_actual < r_actual; i_actual++) {
                    int i = MOD(i_actual, N);

                    dp[l][r][0] = max(dp[l][r][0], dp[l][i][0]);
                    dp[l][r][1] = max(dp[l][r][1], dp[i][r][1]);

                    if (bef[l][i][0] != -INF && bef[i][r][0] != -INF) {
                        bef[l][r][0] = max(bef[l][r][0], bef[l][i][0] + bef[i][r][0]);
                    }
                    if (bef[l][i][1] != -INF && bef[i][r][1] != -INF) {
                        bef[l][r][1] = max(bef[l][r][1], bef[l][i][1] + bef[i][r][1]);
                    }

                    if (stage[l][i]) {
                        dp[l][r][0] = max(dp[l][r][0], 1 + dp[i][r][0]);
                    }
                    if (stage[r][i]) {
                        dp[l][r][1] = max(dp[l][r][1], 1 + dp[l][i][1]);
                    }
                }

                if (stage[l][r]) {
                    int res = 1 + dp[MOD(l + 1, N)][r][1];
                    if (res >= dp[l][r][0]) {
                        dp[l][r][0] = res;
                    }

                    bef[l][r][0] = max(bef[l][r][0], 1);
                }
                if (stage[r][l]) {
                    int res = 1 + dp[l][MOD(r_actual - 1, N)][0];
                    if (res >= dp[l][r][1]) {
                        dp[l][r][1] = res;
                    }

                    bef[l][r][1] = max(bef[l][r][1], 1);
                }
            }
        }

        int ans = 0;
        int starting = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dp[i][j][0] > ans) {
                    ans = dp[i][j][0];
                    starting = i;
                }
                if (dp[i][j][1] > ans) {
                    ans = dp[i][j][1];
                    starting = j;
                }
            }
        }
        if (K == 0) {
            printf("%d\n%d\n", ans, starting + 1);
            return 0;
        }

        // Unite bef(before intersection) with dp(after intersection)
        for (int len = 0; len <= N; len++) {
            for (int l = 0; l < N; l++) {
                int r_actual = l + len - 1;
                int r = MOD(r_actual, N);

                bool g1 = stage[l][r];
                bool g2 = stage[r][l];

                for (int i_actual = l + 1; i_actual < r_actual; i_actual++) {
                    int i = MOD(i_actual, N);

                    int res = -INF;
                    int s = -1;
                    if (g2) {
                        res = bef[l][i][0];
                        s = r;
                    }
                    if (g1 && res < bef[i][r][1]) {
                        res = bef[i][r][1];
                        s = l;
                    }
                    res++;

                    if (res < 0) {
                        continue;
                    }

                    int j1 = upper_bound(adj_list[i].begin(), adj_list[i].end(), r_actual) - adj_list[i].begin();
                    int j2 = lower_bound(adj_list[i].begin(), adj_list[i].end(), N + l) - adj_list[i].begin() - 1;

                    int v = 0;
                    for (int j = max(j1, 0); j <= min(j2, (int)adj_list[i].size() - 1); j++) {
                        int n = adj_list[i][j];
                        v = max(v, 1 + dp[MOD(n, N)][MOD(l - 1 + N, N)][0]);
                        v = max(v, 1 + dp[MOD(r + 1, N)][MOD(n, N)][1]);
                    }

                    if (ans < v + res) {
                        ans = v + res;
                        starting = s;
                    }
                }
            }
        }

        printf("%d\n%d\n", ans, starting + 1);

        return 0;
    }