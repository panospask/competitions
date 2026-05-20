#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

int N, C;
vector<ll> fact;
vector<ll> inv;

vector<int> l, r;
vector<int> v;

vector<int> order;

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

ll calc_inv(ll a) {
    return calc_pow(a, MOD - 2);
}

void precalculate(void) {
    fact.assign(N + 10, 0);

    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    
    inv.resize(N + 10, 0);
    inv[N] = calc_inv(fact[N]);
    for (int i = N - 1; i >= 0; i--) {
        inv[i] = (i + 1) * inv[i + 1] % MOD;
    }
}

ll choose(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }

    ll nom = 1;
    for (int i = n; i > n - k; i--) {
        nom = nom * i % MOD;
    }
    return nom * inv[k] % MOD;
}

void linearize(int node) {
    if (l[node] != -2) {
        linearize(l[node]);
    }
    order.push_back(node);
    if (r[node] != -2) {
        linearize(r[node]);
    }
}

// m boxes k total value
ll distribute(int m, int k) {
    return choose(m + k - 1, m - 1);
}

void solve(void) {
    scanf("%d %d", &N, &C);

    l.resize(N);
    r.resize(N);
    v.resize(N);
    order.clear();

    precalculate();

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &l[i], &r[i], &v[i]);
        l[i]--;
        r[i]--;
    }

    linearize(0);

    int prv = 1;
    int cnt = 0;

    ll ans = 1;

    for (int i = 0; i < N; i++) {
        cnt++;

        int u = order[i];
        if (v[u] != -1) {
            ans = ans * distribute(cnt, v[u] - prv) % MOD;
            cnt = 0;
            prv = v[u];
        }
    }
    cnt++;
    ans = ans * distribute(cnt, C - prv) % MOD;

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}