#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n;

int main(void)
{
    scanf("%lld", &n);

    ll curv = 2;
    ll ans = 0;
    int cut = ceil(sqrt(n));

    while (n != 1 && curv <= cut) {
        while (n % curv && curv <= cut)
            curv++;

        int cnt = 0;
        while (n % curv == 0) {
            n /= curv;
            cnt++;
        }

        int cur = 1;
        while (cnt >= cur) {
            ans++;
            cnt -= cur++;
        }
    }

    if (n != 1)
        ans++;

    printf("%lld\n", ans);
    return 0;
}