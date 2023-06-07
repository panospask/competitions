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

        while (h[s.top()] > h[i]) {
            ll width = w[s.top()] + startp[i] - pos[s.top()];
            ans += possible_squares(width, h[s.top()]);
            w[i] += w[s.top()];
            s.pop();

            int hrm = max(h[i], h[s.top()]);
            ans -= possible_squares(width, hrm);

            ans = (((ans % MOD) + MOD) % MOD);
        }

        if (h[i] > h[s.top()])
            s.push(i);
    }

    while (s.size() > 1) {
        ll width = w[s.top()] + pos.back() - pos[s.top()];
        ans += possible_squares(width, h[s.top()]);
        s.pop();

        ans -= possible_squares(width, h[s.top()]);

        ans = (((ans % MOD) + MOD) % MOD);
    }

    printf("%lld\n", ans);
    return 0;
}