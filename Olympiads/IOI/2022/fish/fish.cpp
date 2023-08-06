#include "fish.h"

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int N, M;
vector<int> X, Y, W;

vector<vector<int>> grid;
vector<vector<ll>> best;
vector<vector<ll>> pref;
vector<vector<ll>> opt;

vector<vector<vector<ll>>> dp;

ll first_subtask(void)
{
    // First subtask
    ll ans = 0;
    for (int i = 0; i < M; i++)
        ans += W[i];

    return ans;
}

ll second_subtask(void)
{
    if (N <= 2) {
        ll ans1 = 0;
        ll ans2 = 0;
        for (int i = 0; i < M; i++) {
            if (!X[i])
                ans1 += W[i];
            else
                ans2 += W[i];
        }

        return max(ans1, ans2);
    }
    else {
        vector<ll> pref1(N);
        vector<ll> suff2(N);

        for (int i = 0; i < M; i++) {
            if (!X[i])
                pref1[Y[i]] += W[i];
            else
                suff2[Y[i]] += W[i];
        }

        for (int i = 1; i < N; i++)
            pref1[i] += pref1[i - 1];
        for (int i = N - 2; i >= 0; i--)
            suff2[i] += suff2[i + 1];

        ll ans = max(suff2[0], pref1[N - 1]);
        for (int i = 0; i < N - 1; i++)
            ans = max(ans, pref1[i] + suff2[i + 1]);

        return ans;
    }
}

ll third_subtask(void)
{
    // dp[i]: Build all piers up to i
    vector<ll> dp[2][2];

    vector<int> add(N);
    for (int i = 0; i < M; i++)
        add[X[i]] += W[i];

    dp[0][0].resize(N);
    dp[0][1].resize(N);
    dp[1][0].resize(N);
    dp[1][1].resize(N);

    dp[0][0][1] = dp[1][1][1] = 0;
    dp[0][1][1] = add[0];
    dp[1][0][1] = add[1];
    for (int i = 2; i < N; i++) {
        dp[1][1][i] = max(dp[0][1][i - 1], dp[1][1][i - 1]);
        dp[1][0][i] = max(dp[0][1][i - 1], dp[1][1][i - 1]) + add[i];
        dp[0][0][i] = max(dp[0][0][i - 1], dp[1][0][i - 1]);
        dp[0][1][i] = max(dp[0][0][i - 1] + add[i - 1], dp[1][0][i - 1]);
    }

    ll ans = 0;
    ans = max(ans, dp[0][0][N - 1]);
    ans = max(ans, dp[0][1][N - 1]);
    ans = max(ans, dp[1][0][N - 1]);
    ans = max(ans, dp[1][1][N - 1]);

    return ans;
}

ll max_weights(int n, int m, vector<int> x, vector<int> y, vector<int> w)
{
    N = n;
    M = m;
    X = x;
    Y = y;
    W = w;

    bool sub1 = true, sub2 = true, sub3 = true;
    for (int i = 0; i < M; i++) {
        sub1 = sub1 && (X[i] % 2 == 0);
        sub2 = sub2 && (X[i] <= 1);
        sub3 = sub3 && (Y[i] == 0);
    }

    if (sub1)
        return first_subtask();
    if (sub2)
        return second_subtask();
    if (sub3)
        return third_subtask();


    dp.resize(N, vector<vector<ll>>(N + 1, vector<ll>(N + 1)));
    grid.resize(N, vector<int>(N));
    pref.assign(N, vector<ll>(N + 1, 0));
    best.resize(N, vector<ll>(N + 1));
    opt.assign(N, vector<ll>(N + 1, -INF));

    for (int i = 0; i < M; i++)
        grid[X[i]][Y[i]] += W[i];

    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++) {
            pref[x][y + 1] = pref[x][y] + grid[x][y];
        }

    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= N; j++) {
            if (i > j) {
                dp[1][i][j] = pref[1][i] - pref[1][j];
                opt[1][i] = max(opt[1][i], dp[1][i][j] - pref[1][i]);
            }
            else {
                dp[1][i][j] = pref[0][j] - pref[0][i];
                opt[1][j] = max(opt[1][j], dp[1][i][j] - pref[1][j]);
            }
        }

    for (int p = 2; p < N; p++) {
        for (int j = 0; j <= N; j++) {
            best[p - 1][j] = 0;
            for (int i = 0; i <= N; i++)
                best[p - 1][j] = max(best[p - 1][j], dp[p - 1][i][j]);
        }
        for (int j = 0; j <= N; j++) {
            if (j)
                opt[p - 1][j] = max(opt[p - 1][j], opt[p - 1][j - 1]);
        }
        for (int j = 0; j <= N; j++) {
            opt[p - 1][j] += pref[p - 1][j];
        }

        for (int i = 0; i <= N; i++)
            for (int j = 0; j <= N; j++) {
                dp[p][i][j] = 0;
                if (i > j) {
                    dp[p][i][j] = best[p - 1][i] + pref[p][i] - pref[p][j];
                    opt[p][i] = max(opt[p][i], dp[p][i][j] - pref[p][i]);
                }
                else {
                    dp[p][i][j] = max(best[p - 1][i], opt[p - 1][j]);
                    opt[p][j] = max(opt[p][j], dp[p][i][j] - pref[p][j]);
                }
            }
    }

    ll ans = 0;
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= N; j++)
            ans = max(ans, dp[N - 1][i][j]);

    return ans;
}