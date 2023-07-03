#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, k;
vector<int> a;
vector<ll> pref;

bool can_make(ll x)
{
    int pos = lower_bound(a.begin(), a.end(), x) - a.begin() - 1;
    int cut = n / 2;

    if (pos < cut)
        return true;

    int change = pos - cut + 1;
    ll cost = change * x - (pref[pos + 1] - pref[pos - change + 1]);

    return cost <= k;
}

int main(void)
{
    scanf("%d %d", &n, &k);
    a.resize(n);
    pref.resize(n + 1);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    sort(a.begin(), a.end());

    pref[0] = 0;
    for (int i = 1; i <= n; i++)
        pref[i] = pref[i - 1] + a[i - 1];

    ll r = 1;
    ll l = 0;
    while (can_make(r)) {
        l = r;
        r *= 2;
    }

    while (r > l + 1) {
        ll mid = (l + r) / 2;
        if (can_make(mid))
            l = mid;
        else
            r = mid;
    }

    printf("%lld\n", l);
}