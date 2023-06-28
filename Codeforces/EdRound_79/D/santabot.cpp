#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int MAXV = 1e6;

typedef long long ll;

int n;
int n_inv = 0;

// v[i] is the probability of choosing a valid gift when selecting kid i
vector<ll> v;
vector<vector<int>> a;

// g[i] is the probability of a certain gift being likeable
vector<ll> g;
vector<int> wanted_by;

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

ll calc_inv(int i)
{
    return calc_pow(i, MOD - 2);
}

void calculate_v(int i)
{
    int res = 0;
    for (int j = 0; j < a[i].size(); j++) {
        res = (res + g[a[i][j]]) % MOD;
    }

    // Multiply by the probability of each event happening (1 / n)
    res = res * calc_inv(a[i].size()) % MOD;

    v[i] = res;
}

void calculate_g(int i)
{
    g[i] = (ll)wanted_by[i] * n_inv % MOD;
}

int main(void)
{
    scanf("%d", &n);

    n_inv = calc_inv(n);

    a.resize(n);
    v.resize(n);
    wanted_by.assign(MAXV + 1, 0);
    g.resize(MAXV + 1);

    for (int i = 0; i < n; i++) {
        int k;
        scanf("%d", &k);

        a[i].resize(k);
        for (int j = 0; j < k; j++) {
            scanf("%d", &a[i][j]);
            wanted_by[a[i][j]]++;
        }
    }

    for (int i = 0; i <= MAXV; i++)
        if (wanted_by[i])
            calculate_g(i);

    int res = 0;
    for (int i = 0; i < n; i++) {
        calculate_v(i);
        res = (res + v[i]) % MOD;
    }

    res = res * (ll)n_inv % MOD;

    printf("%d\n", res);

    return 0;
}