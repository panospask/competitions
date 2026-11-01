#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

int N, X;
ll ans = 0;

// dp[i][h]: # of ways to have i heroes alive, and the best one has health h
vector<vector<ll>> dp;

vector<ll> fact;
vector<ll> inv;

ll calc_pow(ll a, ll b) {
    ll c = 1;
    while (b) {
        if (b % 2) {
            c = c * a % MOD;
        }

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

ll choose(ll n, ll k) {
    ll nom = fact[n];
    ll den = inv[k] * inv[n - k] % MOD;

    return nom * den % MOD;
}

void precalculate(void) {
    fact.resize(2 * N + 1);
    inv.resize(2 * N + 1);

    fact[0] = 1;
    for (int i = 1; i <= 2 * N; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    for (int i = 0; i <= 2 *N; i++) {
        inv[i] = calc_pow(fact[i], MOD - 2);
    }
}

void add(ll& a, ll b) {
    a += b;
    a = (a % MOD + MOD) % MOD;
}

int main(void)
{
    scanf("%d %d", &N, &X);

    precalculate();


    dp.resize(N + 1, vector<ll>(X + 1, 0));
    
    ll ans = 0;

    // Initialize all "final" rounds
    for (int i = 2; i <= N; i++) {
        int damage = i - 1;
        ll prv = 0;
        for (int x = 1; x <= min(damage, X); x++) {
            // This is the max health
            ll ways = calc_pow(x, i);
            add(ways, -prv);
            add(prv, ways);
            dp[i][x] = ways;
        }
    }

    for (int i = 0; i <= N; i++) {
        for (int h = 0; h < X; h++) {
            for (int j = 0; j + i <= N; j++) {
                /* Add j more heroes (could be 0), all of which will be first round elim
                 bump all previous heroes so we reach dp[i][h] after the first round
                */
                if (i == 0 && j < 2) {
                    // This means a single winner
                    // Or an empty game
                    continue;
                }

                int damage = i + j - 1;
                if (damage + h > X) {
                    continue;
                }

                ll ways = dp[i][h] * choose(i + j, i) % MOD * calc_pow(damage, j) % MOD;
                add(dp[i + j][damage + h], ways);
            }
        }
    }

    for (int h = 0; h <= X; h++) {
        add(ans, dp[N][h]);
    }

    printf("%lld\n", ans);
}