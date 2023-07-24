#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXD = 18;
const int DIGCNT = 10;

ll A, B;
ll dp[MAXD + 1][DIGCNT + 1][DIGCNT + 1][2][2];
vector<int> number;

ll calc_dp(int pos = MAXD, int p1 = DIGCNT, int p2 = DIGCNT, bool smaller = false, bool leadz = true)
{
    if (pos == -1)
        return 1;

    if (dp[pos][p1][p2][smaller][leadz] != -1)
        return dp[pos][p1][p2][smaller][leadz];

    int v = number[pos];
    dp[pos][p1][p2][smaller][leadz] = 0;
    for (int l = 0; l < DIGCNT; l++) {
        if (l == 0 && leadz) {
            dp[pos][p1][p2][smaller][leadz] += calc_dp(pos - 1, p2, DIGCNT, smaller || v, true);
        }
        else {
            if (l == p1 || l == p2)
                continue;

            if (l < v) {
                dp[pos][p1][p2][smaller][leadz] += calc_dp(pos - 1, p2, l, true, false);
            }
            else if (l == v) {
                dp[pos][p1][p2][smaller][leadz] += calc_dp(pos - 1, p2, l, smaller, false);
            }
            else {
                if (smaller)
                    dp[pos][p1][p2][smaller][leadz] += calc_dp(pos - 1, p2, l, smaller, false);
            }
        }
    }

    return dp[pos][p1][p2][smaller][leadz];
}

void setnum(ll A)
{
    memset(dp, -1, sizeof(dp));
    number.clear();

    for (int i = 0; i < MAXD + 1; i++) {
        number.push_back(A % 10);
        A /= 10;
    }
}

int main(void)
{
    scanf("%lld %lld", &A, &B);

    ll ans = 0;
    if (A != 0) {
        setnum(A - 1);
        ans -= calc_dp();
    }
    setnum(B);
    ans += calc_dp();

    printf("%lld\n", ans);
}