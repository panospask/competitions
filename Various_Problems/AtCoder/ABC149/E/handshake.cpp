#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXINC = 1e5;

int n;
ll m;
vector<int> a;
vector<ll> pref;
ll ans = 0;

ll handshakes_made(int minv)
{
    ans = 0;
    ll res = 0;
    int r = n - 1;
    for (int l = 0; l < n; l++) {
        while (r >= 0 && a[l] + a[r] < minv) {
            r--;
        }

        res += r + 1;
        if (r >= 0)
            ans += pref[r] + (ll)(r + 1) * a[l];
    }

    return res;
}

int main(void)
{
    scanf("%d %lld", &n, &m);
    a.resize(n);
    pref.resize(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        pref[i] = !i ? a[i] : pref[i - 1] + a[i];
    }

    int l = 0;
    int r = 2 * MAXINC + 1;
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (handshakes_made(mid) >= m)
            l = mid;
        else
            r = mid;
    }

    ll extra = handshakes_made(l) - m;
    ans -= extra * l;

    printf("%lld\n", ans);

    return 0;
}