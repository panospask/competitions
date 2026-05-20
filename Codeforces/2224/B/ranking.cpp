#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

struct SegTree {
    int size;
    vector<ll> tree;

    void init(int N){
        size = 1;
        while (size < N) {
            size = size * 2;
        }

        tree.assign(2 * size, 0);
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid){
            add(i, v, 2 * x + 1, lx, mid);
        }
        else {
            add(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = tree[2 * x + 1] + tree[2 * x +  2];
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ll c1 = calc(l ,r, 2 * x + 1, lx, mid);
        ll c2 = calc(l, r, 2 * x + 2, mid, rx);
        return c1 + c2;
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

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

int N, M;
SegTree st;
vector<int> a, b;
void solve(void) {
    scanf("%d", &N);

    a.resize(N);
    b.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }
    sort(b.begin(), b.end());

    vector<ll> v;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            v.push_back((ll)a[i] * b[j]);
        }
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    M = v.size();
    st.init(M);

    ll total = 0;
    for (int i = N - 1; i >= 0; i--) {
        vector<int> p;
        for  (int j = 0; j < N; j++) {
            ll cur = (ll)a[i] * b[j];
            int pos = lower_bound(v.begin(), v.end(), cur) - v.begin();

            total += st.calc(0, pos);
            p.push_back(pos);
        }
        for (auto pos : p) {
            st.add(pos, 1);
        }

        int cnt = 0;
        for (int i2 = i + 1; i2 < N; i2++) {
            if (a[i] > a[i2]) {
                cnt++;
            }
        }

        total -= (ll)N * cnt;

        total %= MOD;
    }

    ll ans = total * calc_inv((ll)N * (N - 1) % MOD) % MOD;
    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}