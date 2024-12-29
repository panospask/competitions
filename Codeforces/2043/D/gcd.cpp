#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void solve(void)
{
    ll l, r, g;
    scanf("%lld %lld %lld", &l, &r, &g);

    ll big = (r + 1) / g - 1;
    ll small = (l - 1) / g + 1;

    if (small * g > r || big * g < l) {
        printf("-1 -1\n");
    }
    else {
        printf("%lld %lld\n", small * g, big * g);
    }
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}