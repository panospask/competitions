#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef __int128_t lll;

ll N, M, K;

bool satisfy(ll x)
{
    ll G = 0;
    ll rem_days = K;

    while (rem_days && G < N) {
        ll Y = (N - G) / x;

        if (Y < M) {
            return (lll)M * rem_days >= N - G;
        }

        ll maxremove = (N - G) % x;
        ll daysremove = maxremove / Y + 1;

        daysremove = min(rem_days, daysremove);
        G += daysremove * Y;
        rem_days -= daysremove;
    }

    return G >= N;
}

int main(void)
{
    freopen("loan.in", "r", stdin);
    freopen("loan.out", "w", stdout);

    scanf("%lld %lld %lld", &N, &K, &M);

    ll l = 1;
    ll r = 2;
    while (satisfy(r)) {
        l = r;
        r *= 2;
    }

    while (r > l + 1) {
        ll mid = (l + r) / 2;
        if (satisfy(mid))
            l = mid;
        else
            r = mid;
    }

    printf("%lld\n", l);
    return 0;
}