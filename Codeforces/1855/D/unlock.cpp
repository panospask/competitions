#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5;

typedef long long ll;

int N;
vector<int> v;
vector<ll> pref;
ll tot = 0;

void solve(void)
{
    scanf("%d", &N);

    v.resize(N);
    pref.resize(2 * MAXN);
    tot = 0;
    for (int i = 0; i < N; i++) {
        if (tot < i) {
            N = i;
            v.resize(N);
            break;
        }

        scanf("%d", &v[i]);
        tot += v[i];
        pref[i] = v[i];
        if (i)
            pref[i] += pref[i - 1];
    }
    for (int i = N; i < 2 * MAXN; i++)
        pref[i] = pref[i - 1];

    bitset<2 * MAXN> dp;
    dp = 1;

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        dp |= dp << v[i];

        if (dp[i])
            ans = max (ans, pref[i] - i);
        dp[i] = 0;
    }
    for (int i = N; i < 2 * MAXN; i++) {
        if (dp[i])
            ans = max(ans, pref[i] - i);
    }

    printf("%lld\n", ans);

    return;
}

int main(void)
{
    int t;
    t = 1;

    while (t--)
        solve();

    return 0;
}