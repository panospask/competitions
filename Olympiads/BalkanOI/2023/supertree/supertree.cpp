#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) (((var) & (1ll << pos)) != 0)
#define mp make_pair
#define pb push_back

using namespace std;

const int MOD = (int)1e9 + 7;
const int BITS = 60;

typedef long long ll;

void add(ll& a, ll b)
{
    a += b;

    if (a > MOD)
        a -= MOD;
    else if (a < 0)
        a += MOD;
}

vector<ll> twopow;

int N, Q;
vector<vector<bool>> cleared;
vector<vector<int>> kids;
vector<ll> a, f;

ll super = 0;
ll sum = 0;
ll squaresum = 0;

ll calc_power(void)
{
    return (2 * super + squaresum) % MOD;
}

void clearbit(int node, int b)
{
    if (cleared[node][b]) {
        return;
    }

    add(sum, -f[node]);
    add(squaresum, -f[node] * f[node] % MOD);
    add(super, -f[node] * sum % MOD);

    add(f[node], -twopow[b]);

    add(super, f[node] * sum % MOD);
    add(squaresum, f[node] * f[node] % MOD);
    add(sum, f[node]);

    for (auto kid : kids[node])
        clearbit(kid, b);

    cleared[node][b] = true;
}

void initialize(int node)
{
    for (int b = 0; b < BITS; b++) {
        if (CHECK_BIT(f[node], b))
            cleared[node][b] = false;
    }

    for (auto kid : kids[node]) {
        f[kid] = a[kid] & f[node];
        initialize(kid);
    }
    f[node] %= MOD;

    add(super, f[node] * sum % MOD);
    add(sum, f[node]);
    add(squaresum, f[node] * f[node] % MOD);
}

void calc_twopow(void)
{
    twopow.resize(BITS);
    twopow[0] = 1;

    for (int i = 1; i < BITS; i++)
        twopow[i] = twopow[i - 1] * 2 % MOD;
}

void print_ans(void)
{
    printf("%lld %lld\n", calc_power(), super);
}

int main(void)
{
    calc_twopow();

    scanf("%d %d", &N, &Q);

    cleared.assign(N, vector<bool>(BITS, true));
    kids.resize(N);
    a.resize(N);
    f.resize(N);

    for (int i = 1; i < N; i++) {
        int p;
        scanf("%d", &p);
        kids[p].pb(i);
    }
    for (int i = 0; i < N; i++) {
        scanf("%lld", &a[i]);
    }

    f[0] = a[0];
    initialize(0);

    print_ans();
    for (int q = 0; q < Q; q++) {
        int v;
        ll x;

        scanf("%d %lld", &v, &x);

        for (int b = 0; b < BITS; b++) {
            if (!CHECK_BIT(x, b))
                clearbit(v, b);
        }

        print_ans();
    }

    return 0;
}