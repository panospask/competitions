#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXD = 18;
const int ALLOWED = 3;

ll dp[MAXD + 1][ALLOWED + 1][2];
vector<int> NUM;

ll calculate_dp(int pos = MAXD, int let_allowed = 3, bool smaller = false)
{
    if (pos == -1)
        return 1;

    if (dp[pos][let_allowed][smaller] != -1)
        return dp[pos][let_allowed][smaller];

    int at = NUM[pos];
    dp[pos][let_allowed][smaller] = 0;

    for (int l = 0; l < 10; l++) {
        if (!let_allowed && l)
            continue;

        if (l < at) {
            dp[pos][let_allowed][smaller] += calculate_dp(pos - 1, let_allowed - (bool)l, true);
        }
        else if (l == at) {
            dp[pos][let_allowed][smaller] += calculate_dp(pos - 1, let_allowed - (bool)l, smaller);
        }
        else {
            if (smaller)
                dp[pos][let_allowed][smaller] += calculate_dp(pos - 1, let_allowed - (bool)l, smaller);
        }
    }

    return dp[pos][let_allowed][smaller];
}

void init_state(ll A)
{
    memset(dp, -1, sizeof(dp));

    NUM.clear();
    for (int i = 0; i < MAXD + 1; i++) {
        NUM.push_back(A % 10);
        A /= 10;
    }
}

int main(void)
{
    int T;
    scanf("%d", &T);

    while (T--) {
        ll A, B;
        scanf("%lld %lld", &A, &B);

        ll ans = 0;

        init_state(A - 1);
        ans -= calculate_dp();

        init_state(B);
        ans += calculate_dp();

        printf("%lld\n", ans);
    }

    return 0;
}