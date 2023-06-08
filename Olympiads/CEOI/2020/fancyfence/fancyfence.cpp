#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = ((int)1e9 + 7);

int n;
vector<ll> pos;
vector<int> h;
vector<ll> w;
vector<int> startp;
ll ans = 0;

ll possible_squares(ll x, int y)
{
    x %= MOD;
    y %= MOD;

    ll f1 = ((ll) x * (x + 1) / 2) % MOD;
    ll f2 = ((ll) y * (y + 1) / 2) % MOD;

    return (ll)f1 * f2 %  MOD;
}

int main(void)
{
    scanf("%d", &n);
    pos.resize(n + 1);
    h.resize(n + 1);
    startp.resize(n + 1);
    w.resize(n + 1);

    h[0] = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &h[i]);

    pos[0] = 0;
    w[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &w[i]);
        pos[i] = w[i] + pos[i - 1];
        startp[i] = pos[i] - w[i];
    }

    stack<int> s;
    s.push(0);

    for (int i = 1; i <= n; i++) {

        ll prv_add = 0;

        while (h[s.top()] >= h[i]) {
            w[s.top()] += prv_add;
            ll width = w[s.top()];
            ans += possible_squares(width, h[s.top()]);
            prv_add = w[s.top()];
            s.pop();

            int hrm = max(h[i], h[s.top()]);
            ans -= possible_squares(width, hrm);

            ans = (((ans % MOD) + MOD) % MOD);
        }

        w[i] += prv_add;
        s.push(i);
    }

    ll prv_add = 0;

    while (s.size() > 1) {
        w[s.top()] += prv_add;

        ll width = w[s.top()];
        prv_add = w[s.top()];
        ans += possible_squares(width, h[s.top()]);

        if (h[s.top()] == 1)
            assert(width == pos.back());

        s.pop();

        ans -= possible_squares(width, h[s.top()]);

        ans = (((ans % MOD) + MOD) % MOD);
    }

    printf("%lld\n", ans);
    return 0;
}