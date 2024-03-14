#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef __int128_t lll;

int n, Q;
vector<ll> d1, d2;
vector<int> primes;

void generate_multiples(ll x, int pos, int fin, vector<int>& nums, vector<ll>& res)
{
    if (pos >= fin) {
        res.push_back(x);
        return;
    }

    lll cur = 1;

    while ((lll)x * cur < 1e18) {
        generate_multiples(x * cur, pos + 2, fin, nums, res);
        cur *= nums[pos];
    }
}

ll before(ll x)
{
    ll ans = 0;
    int p2 = d2.size() - 1;

    for (int i = 0; i < d1.size(); i++) {
        while (p2 >= 0 && (lll)d1[i] * d2[p2] > x)
            p2--;

        ans += p2 + 1;
    }

    return ans;
}

int main(void)
{
    scanf("%d", &n);

    primes.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &primes[i]);
    sort(primes.begin(), primes.end());

    generate_multiples(1, 0, n, primes, d1);
    generate_multiples(1, 1, n, primes, d2);

    sort(d1.begin(), d1.end());
    sort(d2.begin(), d2.end());

    Q = 1;
    while (Q--) {
        ll k;
        scanf("%lld", &k);

        ll l = 0;
        ll r = 1e18 + 1;

        while (r > l + 1) {
            ll mid = (l + r) / 2;
            if (before(mid) >= k)
                r = mid;
            else
                l = mid;
        }

        printf("%lld\n", r);
    }

    return 0;
}