#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXDIGITS = 39;
const int BASE = 3;

int Q;
vector<int> x;

// Constant difference between x and y at the pairs (x_i, y_i)
vector<int> add;

/* dp[pos][quot][under]:
 * Count of pairs (i, i + add) such that:
 * We have placed digits in positions [pos...N]
 * The quotient of our number divided by BASE^(N - pos) equals quot
 * 
 * under is a boolean variable denoting if we have gone under the number x
 * when picking a previous (in the range[0...pos - 1]) position.
 */
ll dp[MAXDIGITS + 1][BASE][2];

void calculate_dp(int pos, int quot, bool under)
{
    if (dp[pos][quot][under] != -1) {
        return;
    }

    if (pos == x.size()) {
        dp[pos][quot][under] = (quot == 0);
        return;
    }

    dp[pos][quot][under] = 0;
    for (int d = 0; d < BASE; d++) {
        bool new_under = under || (d < x[pos]);

        if (!new_under && x[pos] < d) {
            continue;
        }

        for (int q = 0; q < BASE; q++) {
            // We want the digits d and d + add[pos] + q to have same parity
            // Also (x[pos] + add + q) / 3 must equal quot
            if (((d + add[pos] + q) / 3 == quot) && (((d + add[pos] + q) % 3) % 2 == d % 2)) {
                calculate_dp(pos + 1, q, new_under);
                dp[pos][quot][under] += dp[pos + 1][q][new_under];
            }
        }
    }
}

void clear(void)
{
    for (int pos = 0; pos <= x.size(); pos++) {
        for (int d = 0; d < BASE; d++) {
            for (int p = 0; p < 2; p++) {
                dp[pos][d][p] = -1;
            }
        }
    }
}

void make_target(ll a, ll diff)
{
    // y = a + diff

    x.clear();
    while (a) {
        x.push_back(a % BASE);
        a /= BASE;
    }

    add.clear();
    while (diff) {
        add.push_back(diff % BASE);
        diff /= BASE;
    }

    while (x.size() > add.size()) {
        add.push_back(0);
    }
    while (add.size() > x.size()) {
        x.push_back(0);
    }

    reverse(x.begin(), x.end());
    reverse(add.begin(), add.end());
}

void solve(void)
{
    ll a, y, d;
    scanf("%lld %lld %lld", &d, &y, &a);

    if (a > y) {
        swap(a, y);
    }

    ll diff = y - a;

    make_target(a + d, diff);
    clear();
    calculate_dp(0, 0, false);
    ll res = dp[0][0][false];

    if (a) {
        make_target(a - 1, diff);
        clear();
        calculate_dp(0, 0, false);
        res -= dp[0][0][false];
    }

    printf("%lld\n", res);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}