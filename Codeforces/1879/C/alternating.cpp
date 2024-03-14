#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

typedef long long ll;

const int MOD = 998244353;

int N;

vector<ll> fact;
vector<ll> inv;
string s;

ll calc_inv(ll a)
{
    ll c = 1;
    int b = MOD - 2;

    while (b) {
        if (b % 2)
            c = c * a % MOD;

        b /= 2;
        a = a * a % MOD;
    }

    return c;
}

ll choose(int a, int b)
{
    if (a < b)
        return 0;

    ll nom = fact[a];
    ll den = inv[a - b] * inv[b] % MOD;

    return nom * den % MOD;
}

void solve(void)
{
    cin >> s;

    int len = 0;
    char prv = s.front();

    // A different character in order to also process last continuous
    s.push_back('T');
    N = s.size();

    ll ans = 1;
    int del = 0;

    for (int i = 0; i < N; i++) {
        if (s[i] != prv) {
            // End of continuous
            ans = ans * fact[len] % MOD * choose(del + len - 1, len - 1) % MOD;
            del += len - 1;

            len = 1;
            prv = s[i];
        }
        else {
            len++;
        }
    }

    printf("%d %lld\n", del, ans);
}

void precalc(void)
{
    fact.resize(MAXN + 1);
    inv.resize(MAXN + 1);

    fact[0] = 1;
    for (int i = 0; i < MAXN; i++)
        fact[i + 1] = fact[i] * (i + 1) % MOD;

    inv[MAXN] = calc_inv(fact[MAXN]);
    for (int i = MAXN - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

int main(void)
{
    int t;
    scanf("%d", &t);

    precalc();

    while (t--)
        solve();

    return 0;
}