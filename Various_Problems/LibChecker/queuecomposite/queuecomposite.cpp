#include <bits/stdc++.h>
#define MOD 998244353
#define f first
#define s second
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

queue<pi> q;
ll a, b;
int n;

ll calc_pow(ll a, int b)
{
    ll c = 1;

    while (b) {
        if (b % 2)
            c = c * a % MOD;

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

ll calc_inv(int a)
{
    return calc_pow(a, MOD - 2);
}

int main(void)
{
    scanf("%d", &n);

    a = 1;
    b = 0;

    while (n--) {
        int op;
        scanf("%d", &op);

        if (op == 0) {
            int cur_a, cur_b;
            scanf("%d %d", &cur_a, &cur_b);
            q.push(mp(cur_a, cur_b));

            b = (cur_b + b * cur_a) % MOD;
            a = a * cur_a % MOD;
        }
        else if (op == 1) {
            int cur_a, cur_b;
            tie(cur_a, cur_b) = q.front();
            q.pop();

            a = a * calc_inv(cur_a) % MOD;
            b = b - cur_b * a % MOD;
            b = (b + MOD) % MOD;

        }
        else {
            int x;
            scanf("%d", &x);

            ll ans = ((ll) x * a + b) % MOD;

            printf("%lld\n", ans);
        }
    }

    return 0;
}