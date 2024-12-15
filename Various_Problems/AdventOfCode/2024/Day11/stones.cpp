#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

map<pli, ll> found;

ll count(ll v, int turns)
{
    if (turns == 0) {
        return 1;
    }

    if (found.count(mp(v, turns))) {
        return found[mp(v, turns)];
    }

    ll res = 0;

    if (v == 0) {
        res = count(1, turns - 1);
    }
    else {
        int digits = 0;
        ll temp = v;
        while (temp) {
            digits++;
            temp /= 10;
        }

        if (digits % 2) {
            res = count(v * 2024, turns - 1);
        }
        else {
            ll t1 = 0;
            ll p = 1;
            temp = v;
            for (int i = 0; i < digits / 2; i++) {
                t1 = t1 + p * (temp % 10);
                temp /= 10;
                p *= 10;
            }
            ll t2 = 0;
            p = 1;
            for (int i = digits / 2; i < digits; i++) {
                t2 = t2 + p * (temp % 10);
                temp /= 10;
                p *= 10;
            }

            res = count(t1, turns - 1) + count(t2, turns - 1);
        }
    }

    return found[mp(v, turns)] = res;
}

int main(void)
{
    freopen("stones.in", "r", stdin);
    freopen("stones.out", "w", stdout);

    int c = 0;
    ll ans = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        ungetc(c, stdin);

        int v;
        scanf("%d", &v);

        ans += count(v, 75);
    }

    printf("%lld\n", ans);
}