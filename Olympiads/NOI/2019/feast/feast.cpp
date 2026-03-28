#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, K;
vector<int> A;
vector<ll> pref;

vector<ll> dp;
vector<ll> start;
vector<int> cnt;

pair<ll, ll> use(ll x) {
    dp[0] = 0;
    cnt[0] = 0;
    start[0] = 0;
    ll opt = 0;
    for (int i = 1; i <= N; i++) {
        if (dp[i - 1] < pref[i] + start[opt] - x) {
            dp[i] = pref[i] + start[opt] - x;
            cnt[i] = cnt[opt] + 1;
        }
        else {
            dp[i] = dp[i - 1];
            cnt[i] = cnt[i - 1];
        }

        // Open new subarray at i
        start[i] = dp[i] - pref[i];
        if (start[i] < start[opt]) {
            opt = i;
        }
    }

    return {cnt[N], dp[N]};
}

int main(void) {
    scanf("%d %d", &N, &K);

    A.resize(N);
    pref.resize(N + 1);
    dp.resize(N + 1);
    cnt.resize(N + 1);
    start.resize(N + 1);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        pref[i + 1] += A[i];
        pref[i + 1] += pref[i];
    }

    ll l = -1;
    ll r = 1e18;
    while (l + 1 < r) {
        ll mid = (l + r) / 2;

        if (use(mid).first < K) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    ll ans = use(l).second + l * use(l).first;
    printf("%lld\n", ans);
}