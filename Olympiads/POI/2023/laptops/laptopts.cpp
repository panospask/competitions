#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const int INF = 1e6;

int N, L, Q;
ll W, D;
vector<vector<ll>> benches;
vector<vector<int>> extra;
vector<vector<int>> total;
vector<vector<int>> dp;
ll initial = 0;

// Variables for the solve function
vector<ll> pref, diff;

int res(int l, int r)
{
    ll len = pref[r];
    if (l) {
        len -= pref[l - 1];
    }

    return len / D;
}

void calculate(int i, int l, int r, int optl, int optr)
{
    int mid = (l + r) / 2;

    int optv = INF;
    int optpos = optl;
    for (int k = optl; k <= optr; k++) {
        int rs = res(k, i);
        if (mid - rs >= 0 && optv > (i - k) + dp[k - 1][mid - rs]) {
            optv = (i - k) + dp[k - 1][mid - rs];
            optpos = k;
        }
    }

    dp[i][mid] = optv;

    if (mid != l) {
        calculate(i, l, mid, optpos, optr);
        calculate(i, mid, r, optl, optpos);
    }
}

void solve(int b)
{
    int S = benches[b].size();

    /* dp[i][j]:
     * Having processed only the first i students, what is the minimum amount we sould move in
     * order to gain j extra spots?
     */
    dp.assign(S + 1, vector<int>(S + 1, INF));
    diff.resize(S + 1);
    pref.resize(S + 1);

    ll prv = 0;
    for (int i = 0; i < S; i++) {
        diff[i] = benches[b][i] - prv;

        initial += diff[i] / D;
        diff[i] %= D;

        prv = benches[b][i] + D;
    }
    diff[S] = W - prv;

    initial += diff[S] / D;
    diff[S] %= D;

    pref[0] = diff[0];
    for (int i = 1; i <= S; i++) {
        pref[i] = pref[i - 1] + diff[i];
    }

    dp[0][0] = 0;
    for (int i = 1; i <= S; i++) {
        // for (int j = 0; j <= S; j++) {
        //     dp[i][j] = dp[i - 1][j];
        //     prv = i;

        //     for (int k = prv; k > 0; k--) {
        //         // Move the students [k..i] together
        //         int r = res(k, i);
        //         if (j - r >= 0) {
        //             if (dp[i][j] > (i - k) + dp[k - 1][j - r]) {
        //                 dp[i][j] = (i - k) + dp[k - 1][j - r];
        //                 prv = k;
        //             }
        //         }
        //     }
        // }

        calculate(i, 0, S + 1, 1, i);

        int r = res(0, i);
        dp[i][r] = min(dp[i][r], i);
    }

    extra[b] = dp[S];
}

int main(void)
{
    scanf("%d %d %lld %d %lld", &N, &Q, &D, &L, &W);

    initial = 0;
    benches.resize(L);
    extra.resize(L);

    for (int i = 0; i < N; i++) {
        int k;
        ll p;

        scanf("%d %lld", &k, &p);
        k--;
        benches[k].pb(p);
    }
    for (int b = 0; b < L; b++) {
        sort(benches[b].begin(), benches[b].end());
        solve(b);
    }

    total.assign(L + 1, vector<int>(N + 1, INF));
    total[0][0] = 0;

    for (int i = 1; i <= L; i++) {
        for (int j = 0; j <= N; j++) {
            for (int k = 0; k <= j && k < extra[i - 1].size(); k++) {
                total[i][j] = min(total[i][j], total[i - 1][j - k] + extra[i - 1][k]);
            }
        }
    }

    while (Q--) {
        ll M;
        scanf("%lld", &M);

        M -= initial;
        if (M < 0) {
            printf("0\n");
        }
        else if (M > N) {
            printf("-1\n");
        }
        else {
            int res = total[L][M];
            if (res == INF) {
                printf("-1\n");
            }
            else {
                printf("%d\n", res);
            }
        }
    }

    return 0;
}