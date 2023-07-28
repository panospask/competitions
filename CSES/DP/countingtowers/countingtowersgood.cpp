#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = (int)1e9 + 7;

int N;

void solve(void)
{
    scanf("%d", &N);

    int diff = 1;
    int tot = 1;
    int cur_must = 1, cur = 0;
    int must_tot = 1;
    for (int i = 1; i <= N; i++) {
        cur_must += cur;
        if (cur_must > MOD)
            cur_must -= MOD;
        cur = diff + cur_must;
        if (cur > MOD)
            cur -= MOD;

        diff = ((ll)4 * cur - (ll)3 * cur_must) % MOD;
        if (diff < 0)
            diff += MOD;
    }

    printf("%d\n", cur);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}