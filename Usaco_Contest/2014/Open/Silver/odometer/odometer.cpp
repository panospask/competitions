#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXPOS 25
#define BUMP 20

using namespace std;

typedef long long ll;

ll dp[MAXPOS][50][2][2];
string num;

void reset(void)
{
    memset(dp, -1, sizeof(dp));
}

ll calc_dp(const int pos, const int k, const bool isunder, const bool leadzero, const int t1, const int t2)
{
    if (pos == num.size()) {
        if (leadzero)
            return 0;
        if (t2 != -1)
            return k == BUMP;
        else
            return k >= BUMP;
    }

    if (dp[pos][k][isunder][leadzero] != -1)
        return dp[pos][k][isunder][leadzero];

    ll res = 0;
    for (int dig = 0; dig < 10; dig++) {
        // Check both target compatability first
        if (!isunder && dig > (num[pos] - '0'))
            break;
        bool nzero = leadzero && dig == 0;
        if (t2 != -1 && !nzero && dig != t1 && dig != t2)
            continue;
        bool nunder = isunder || dig < (num[pos] - '0');
        int n_k = k;
        if (!nzero) {
            if (dig == t1)
                n_k++;
            else
                n_k--;
        }

        res += calc_dp(pos + 1, n_k, nunder, nzero, t1, t2);
    }

    return dp[pos][k][isunder][leadzero] = res;
}

ll calc_ans_for(ll x)
{
    num = to_string(x);
    ll res = 0;

    for (int dig = 0; dig < 10; dig++) {
        reset();
        res += calc_dp(0, BUMP, false, true, dig, -1);
    }
    for (int d1 = 0; d1 < 10; d1++) {
        for (int d2 = d1 + 1; d2 < 10; d2++) {
            reset();
            res -= calc_dp(0, BUMP, false, true, d1, d2);
        }
    }

    return res;
}

ll x, y;

int main(void)
{
    freopen("odometer.in", "r", stdin);
    freopen("odometer.out", "w", stdout);

    cin >> x >> y;

    ll ans = calc_ans_for(y) - calc_ans_for(x - 1);
    cout << ans << endl;

    return 0;
}