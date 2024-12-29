#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, K;

pair<ll, ll> result(int r)
{
    if (r < K) {
        return {0, 0};
    }

    int mid = (r + 1) / 2;

    ll ans = 0;
    ll times = 0;

    int nxt_r;
    if (r % 2 == 1) {
        times++;
        ans += mid;

        nxt_r = mid - 1;
    }
    else {
        nxt_r = mid;
    }

    auto res = result(nxt_r);
    ans += res.first;
    times += res.second;

    // Now add second time
    times += res.second;
    ans += (nxt_r + r % 2) * res.second + res.first;

    return {ans, times};
}

void solve(void)
{
    scanf("%d %d", &N, &K);

    printf("%lld\n", result(N).first);

    return;
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