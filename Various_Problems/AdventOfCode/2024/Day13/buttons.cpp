#include <bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second

using namespace std;

const int MAX_PRESS = 100;

typedef long long ll;
typedef pair<ll, ll> pi;

pi operator + (pi a, pi b)
{
    return mp(a.fi + b.fi, a.se + b.se);
}
pi operator * (pi a, ll b)
{
    return mp(a.fi * b, a.se * b);
}
pi operator - (pi a, pi b)
{
    return a + (b * -1);
}

ll solve(pi A, pi B, pi T)
{
    // A costs 3
    // B costs 1

    ll m, l;

    ll N = T.fi * A.se - T.se * A.fi;
    ll D = A.se * B.fi - A.fi * B.se;

    if (D == 0) {
        // There is no case where this happens :0
        // Really nice because I could not be bothered with casework.
        exit(0);
    }

    if (N % D != 0) {
        return 0;
    }

    m = N / D;
    l = (T.fi - m * B.fi) / A.fi;

    if (m >= 0 && l >= 0 && A * l + B * m == T) {
        return 3 * l + m;
    }
    return 0;
}

int main(void)
{
    freopen("buttons.in", "r", stdin);
    freopen("buttons.out", "w", stdout);

    ll ans = 0;
    int c = 0;

    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);
        pi A, B, target;
        scanf("Button A: X+%lld, Y+%lld\n", &A.fi, &A.se);
        scanf("Button B: X+%lld, Y+%lld\n", &B.fi, &B.se);
        scanf("Prize: X=%lld, Y=%lld\n", &target.fi, &target.se);
        target = target + mp(10000000000000LL, 10000000000000LL);

        ans += solve(A, B, target);
    }

    printf("%lld\n", ans);

    return 0;
}