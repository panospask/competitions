#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

bool possible(ll target, int pos, vector<ll>& v)
{
    if (target < 0) {
        return false;
    }
    if (pos == v.size()) {
        return target == 0;
    }

    ll cur = v[pos];
    if (target % cur == 0) {
        if (possible(target / cur, pos + 1, v)) {
            return true;
        }
    }

    int digcnt = 0;
    ll temp = cur;
    while (temp) {
        digcnt++;
        temp /= 10;
    }

    bool good = true;
    ll test = target - cur;
    for (int i = 0; i < digcnt; i++) {
        if (test % 10 != 0) {
            good = false;
        }
        test /= 10;
    }

    if (good) {
        if (possible(test, pos + 1, v)) {
            return true;
        }
    }

    return possible(target - cur, pos + 1, v);
}

int main(void)
{
    freopen("calibrate.in", "r", stdin);
    freopen("calibrate.out", "w", stdout);

    int c = 0;
    ll ans = 0;

    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);

        ll target;
        scanf("%lld:", &target);

        vector<ll> v;
        while ((c = getchar()) != '\n') {
            ungetc(c, stdin);
            ll p;
            scanf("%lld", &p);
            v.pb(p);
        }
        reverse(v.begin(), v.end());

        if (possible(target, 0, v)) {
            ans += target;
        }
    }

    printf("%lld\n", ans);

    return 0;
}