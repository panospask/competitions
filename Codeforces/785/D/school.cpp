#include <bits/stdc++.h>

using namespace std;

const int MOD = (int)1e9 + 7;
const int MAXV = 200005;

typedef long long ll;

int n, m;
string s;

vector<ll> fact;
vector<ll> inv;

ll calc_inv(ll a)
{
    ll c = 1;
    int b = MOD - 2;

    while (b) {
        if (b % 2)
            c = c * a % MOD;

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

void factorials(void)
{
    fact.resize(MAXV);
    inv.resize(MAXV);

    fact[0] = 1;
    for (int i = 1; i < MAXV; i++)
        fact[i] = fact[i - 1] * i % MOD;

    inv[MAXV - 1] = calc_inv(fact[MAXV - 1]);
    for (int i = MAXV - 2; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % MOD;
}

ll choose(int a, int b)
{
    if (a < 0 || b < 0)
        return 0;
    if (a < b)
        return 0;

    ll nom = fact[a];
    ll den = inv[b] * inv[a - b] % MOD;

    return nom * den % MOD;
}

int main(void)
{
    cin >> s;

    factorials();

    ll ans = 0;
    int op = 0, cl = 0;
    for (int i = 0; i < s.size(); i++)
        cl += s[i] == ')';

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ')') {
            cl--;
            if (op)
                ans = (ans + choose(op + cl, op - 1)) % MOD;
        }
        else
            op++;
    }

    cout << ans << endl;

    return 0;
}