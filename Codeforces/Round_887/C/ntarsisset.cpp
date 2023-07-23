#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, k;
vector<int> a;

// True if all numbers less than or equal to x die
bool all_die(ll x)
{
    int r = n - 1;

    ll cur = x;
    ll dead = 0;
    for (int i = 0; i < k; i++) {
        while (r >= 0 && a[r] > cur)
            r--;

        cur -= r + 1;
        dead += r + 1;
    }

    return dead >= x;
}

void solve(void)
{
    scanf("%d %d", &n, &k);

    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    ll l = 0;
    ll r = (ll)k * n + 1;
    while (r > l + 1) {
        ll mid = (l + r) / 2;
        if (all_die(mid))
            l = mid;
        else
            r = mid;
    }

    printf("%lld\n", r);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}