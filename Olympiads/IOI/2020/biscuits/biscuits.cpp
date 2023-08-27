#include <bits/stdc++.h>
#include "biscuits.h"
#define CHECK_BIT(val, pos) ((val) & (1ll << pos))

using namespace std;

typedef long long ll;

const int MAXV = 1e5 + 1;
const ll TOTALMAX = 1e18;
const int N = 60;
const int MAXINC = 100;

ll X;
vector<ll> A;

vector<vector<ll>> dp;

ll subtask2(void)
{
    for (int i = 0; i < N; i++) {
        if (A[i] >= X + 2) {
            int keep;
            if ((A[i] - X) % 2) {
                ;
            }
            else {
                ;
            }
        }
    }

    dp.assign(N + 1 , vector<ll>(X, 0));
    dp[N][0] = 1;

    // Everything nullified --> Only 1 solution (0)
    for (int i = N - 1; i >= 0; i--) {
        for (int inc = 0; inc < MAXINC; inc++) {
            dp[i][inc] = dp[i + 1][(inc + A[i]) / 2];
            if (inc + A[i] >= X) {
                dp[i][inc] += dp[i + 1][(inc + A[i] - X) / 2];
            }
        }
    }

    return dp[0][0];
}
bool can_make(ll v)
{
    vector<ll> tmp = A;

    for (int i = 0; i < N; i++) {
        if (CHECK_BIT(v, i)) {
            if (tmp[i] >= X)
                tmp[i] -= X;
            else
                return false;
        }

        if (i != N - 1)
            tmp[i + 1] += tmp[i] / 2;
    }

    return true;
}

ll count_tastiness(ll x, vector<ll> a)
{
    A = a;
    A.resize(N);
    X = x;

    if (x <= 10000) {
        return subtask2();
    }

    ll ans = 0;
    for (int v = 0; v < MAXV; v++)
        if (can_make(v))
            ans++;

    return ans;
}