#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXD = 18;
const int DIGCNT = 10;

ll dp[MAXD + 1][DIGCNT][2][2];
vector<int> number;

ll calc_dp(int pos = MAXD, int prv = 0, bool smaller = false, bool leadz = true)
{
    if (pos == -1)
        return 1;

    if (dp[pos][prv][smaller][leadz] != -1)
        return dp[pos][prv][smaller][leadz];

    ll res = 0;
    int v = number[pos];

    for (int l = 0; l < 10; l++) {
        bool newz = leadz && !l;

        if (l == prv && !newz)
            continue;

        if (l < v) {
            res += calc_dp(pos - 1, l, true, newz);
        }
        else if (l == v) {
            res += calc_dp(pos - 1, l, smaller, newz);
        }
        else {
            if (smaller)
                res += calc_dp(pos - 1, l, smaller, newz);
        }
    }

    return dp[pos][prv][smaller][leadz] = res;
}

void setnum(ll A)
{
    memset(dp, -1, sizeof(dp));
    number.clear();
    for (int i = 0; i < MAXD  + 1; i++) {
        number.push_back(A % 10);
        A /= 10;
    }
}

ll A, B;

int main(void)
{
    scanf("%lld %lld", &A, &B);

    ll ans = 0;
    if (A) {
        setnum(A - 1);
        ans -= calc_dp();
    }

    setnum(B);
    ans += calc_dp();

    printf("%lld\n", ans);

    return 0;
}