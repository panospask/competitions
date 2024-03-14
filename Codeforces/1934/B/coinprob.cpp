#include <bits/stdc++.h>

using namespace std;

const int MAXCALC = 300;

int N;
vector<int> a;
vector<int> dp;

void precalc(void)
{
    dp.resize(MAXCALC + 1);
    dp[0] = 0;
    a = {1, 3, 6, 10, 15};

    for (int s = 1; s <= MAXCALC; s++) {
        dp[s] = s;
        for (auto i : a) {
            if (s - i >= 0) {
                dp[s] = min(dp[s], dp[s - i] + 1);
            }
        }
    }
}

void solve(void)
{
    scanf("%d", &N);

    int pref = 0;
    if (N > MAXCALC) {
        pref = (N - MAXCALC) / 15;
        N = N - 15 * pref;
        if (N > MAXCALC) {
            pref++;
            N -= 15;
        }
    }

    printf("%d\n", dp[N] + pref);
}

int main(void)
{
    precalc();

    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}