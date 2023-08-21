#include "tickets.h"
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const ll INF = 1e18;

// dp[i][c]: Best value of being up to i with c maximums
vector<vector<ll>> dp;
vector<vector<int>> prv;
vector<vector<int>> x;

vector<pi> maxs;
vector<pi> mins;

vector<vector<ll>> pref;
vector<vector<ll>> suff;

vector<vector<int>> s;

int N, M, K;

ll subtask_2(void)
{
    // It is optimal for each of the K groups to have N / 2 1s and N / 2 0s
    vector<pi> cnt(N);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            if (x[i][j])
                break;

            cnt[i].first++;
        }

    int best[2];
    best[0] = best[1] = 0;
    for (int i = 0; i < N; i++) {
        best[0] += min(cnt[i].first, K);
        best[1] += min(M - cnt[i].first, K);

        cnt[i].second = i;
    }

    ll ans = min(best[0], best[1]);
    if (best[0] < best[1]) {
        // Always use the zeroes
        int at = 0;
        int rem = min(best[0], K * N / 2);
        vector<bool> done;
        for (int i = 0; i < N; i++) {
            done.assign(K, false);
            int j = 0;
            while (j < min(K, rem) && x[i][j] == 0) {
                s[i][j] = at;
                done[at] = true;
                j++;
                at = (at + 1) % K;
            }
            rem -= j;

            int cur = 0;
            for (int k = M - 1; k > M - 1 - (K - j); k--) {
                while (done[cur])
                    cur++;

                s[i][k] = cur++;
            }
        }
    }
    else if (best[1] < best[0]) {
        int at = 0;
        vector<bool> done;
        int rem = min(best[1], K * N / 2);
        for (int i = 0; i < N; i++) {
            done.assign(K, false);
            int j = 0;
            while (j < min(K, rem) && x[i][M - j - 1] == 1) {
                s[i][M - j - 1] = at;
                done[at] = true;
                j++;
                at = (at + 1) % K;
            }
            rem -= j;

            int cur = 0;
            for (int k = M - 1; k > M - 1 - (K - j); k--) {
                while (done[cur])
                    cur++;

                s[i][M - k - 1] = cur++;
            }
        }
    }
    else {
        for (int i = 0; i < N; i++) {
            // Enter equal number of zeros and ones
        }
    }
    allocate_tickets(s);

    return ans;
}

ll subtask(void)
{
    vector<pi> values;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            values.pb(mp(x[i][j], i));
    sort(values.rbegin(), values.rend());

    // The upper M * N / 2 are maxs
    vector<int> cnt(N);
    for (int i = 0; i < M * N / 2; i++)
        cnt[values[i].second]++;

    int at = 0;
    vector<bool> done;
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        done.assign(K, false);
        for (int j = M - 1; j > M - 1 - cnt[i]; j--) {
            s[i][j] = at;
            done[at] = true;
            at = (at + 1) % K;

            ans += x[i][j];
        }
        int cur = 0;
        for (int j = 0; j <= M - 1 - cnt[i]; j++) {
            while (done[cur])
                cur++;
            s[i][j] = cur++;

            ans -= x[i][j];
        }
    }

    allocate_tickets(s);

    return ans;
}

void divide(int i, int l, int r, int optl, int optr)
{
    if (l == r)
        return;

    int mid = (l + r) / 2;
    // Calculate the one of mid

    for (int add = optl; add <= optr && add <= mid; add++) {
        if (dp[i][mid] < dp[i - 1][mid - add] - pref[i - 1][K - add] + suff[i - 1][M - add]) {
            dp[i][mid] = dp[i - 1][mid - add] - pref[i - 1][K - add] + suff[i - 1][M - add];
            prv[i][mid] = mid - add;
        }
    }

    divide(i, l, mid, optl, mid - prv[i][mid]);
    divide(i, mid + 1, r, mid - prv[i][mid], optr);
}

ll find_maximum(int k, vector<vector<int>> X)
{
    x = X;
    N = x.size();
    M = x[0].size();
    K = k;
    s.assign(N, vector<int>(M, -1));

    if (K == M) {
        return subtask();
    }

    bool sub2 = true;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            sub2 = sub2 && x[i][j] <= 1;

    if (sub2)
        return subtask_2();

    pref.resize(N, vector<ll>(M + 1));
    suff.resize(N, vector<ll>(M + 1));
    for (int i = 0; i < N; i++) {
        pref[i][0] = 0;
        for (int j = 0; j < M; j++)
            pref[i][j + 1] = pref[i][j] + x[i][j];

        suff[i][M] = 0;
        for (int j = M - 1; j >= 0; j--)
            suff[i][j] = suff[i][j + 1] + x[i][j];
    }

    dp.assign(N + 1, vector<ll>(K * N / 2 + 1, -INF));
    prv.assign(N + 1, vector<int>(K * N / 2 + 1, -1));
    dp[0][0] = 0;

    for (int i = 1; i <= N; i++)
        divide(i, 0, K * N / 2 + 1, 0, K);


    ll ans = dp[N][K * N / 2];

    int i = N;
    int j = K * N / 2;

    vector<bool> done;

    int at = 0;
    while (i) {
        done.assign(K, false);
        int n_i = i - 1;
        int n_j = prv[i][j];

        // Get the number of maximums from n_i

        int diff = j - n_j;
        for (int m = M - 1; m > M - 1 - diff; m--) {
            maxs.pb(mp(x[n_i][m], n_i));
            s[n_i][m] = at;
            done[at] = true;
            at = (at + 1) % K;
        }

        int c = 0;
        for (int m = 0; m < K - diff; m++) {
            mins.pb(mp(x[n_i][m], n_i));
            while (done[c])
                c++;

            s[n_i][m] = c++;
        }
        for (int m = K - diff; m <= M - 1 - diff; m++) {
            s[n_i][m] = -1;
        }

        i = n_i;
        j = n_j;
    }

    allocate_tickets(s);

    return dp[N][K * N / 2];
}
