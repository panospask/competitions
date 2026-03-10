#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

const int MOD = 998244353;

pli operator + (pli a, pli b) {
    return {a.first + b.first, a.second + b.second};
}

// My EDU code
struct segtree {

    vector<pli> tree;
    int size;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(size * 2, {0, 0});
    }

    void set(int pos, ll val, int x, int l, int r) {
        if (l == r - 1) {
            tree[x].first = val;
            tree[x].second = 1;
            return;
        }

        int mid = (l + r) / 2;
        if (pos < mid)
            set(pos, val, 2 * x + 1, l, mid);
        else 
            set(pos, val, 2 * x + 2, mid, r);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void set(int pos, ll val) {
        set(pos, val, 0, 0, size);
    }

    pli calc(int l, int r, int x, int l_x, int r_x) {
        if (l >= r_x || l_x >= r) {
            // Non intersecting segments
            return {0, 0};
        }
        if (l <= l_x && r_x <= r) {
            // The query range is fully contained
            return tree[x];
        }

        int mid = (l_x + r_x) / 2;
        auto s1 = calc(l, r, 2 * x + 1, l_x, mid);
        auto s2 = calc(l, r, 2 * x + 2, mid, r_x);

        return s1 + s2;
    }
    pli calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }

    int find(int k, int x, int lx, int rx) {
        if (lx == rx - 1)
            return lx;

        int mid = (lx + rx) / 2;
        if (tree[2 * x + 1].second > k)
            return find(k, 2 * x + 1, lx, mid);
        else 
            return find(k - tree[2 * x + 1].second, 2 * x + 2, mid, rx);
    }
    int find(int k) {
        return find(k, 0, 0, size);
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

int M;
vector<ll> v;
vector<ll> A;

segtree st;

int find(ll c) {
    return lower_bound(v.begin(), v.end(), c) - v.begin();
}

ll lefttotal(ll v) {
    int p = find(v);

    pli res = st.calc(0, p);
    return res.second * v - res.first;
}

ll righttotal(ll v) {
    int p = find(v);

    pli res = st.calc(p + 1, M);
    return res.first - res.second * v;
}

bool check(int mid) {
    int p1 = st.find(mid - 1);
    int p2 = st.find(mid + 1);
    ll v1 = st.calc(p1, p1 + 1).first;
    ll v2 = st.calc(p2, p2 + 1).first;

    return lefttotal(v1) >= righttotal(v2);
}

void solve(void) {
    scanf("%d", &M);

    v.clear();
    A.resize(M);

    for (int i = 0; i < M; i++) {
        scanf("%lld", &A[i]);
        v.pb(A[i]);
    }

    sort(v.begin(), v.end());

    st.init(M);

    for (int i = 0; i < M; i++) {
        st.set(find(A[i]), A[i]);

        if (i >= 2) {
            // Find the first card s.t. left expected >= right expected
            int l = 0;
            int r = i;

            while (l + 1 < r) {
                int mid = (l + r) / 2;
                if (check(mid)) {
                    r = mid;
                }
                else {
                    l = mid;
                }
            }

            int p1 = st.find(l);
            int p2 = st.find(r);
            ll v1 = st.calc(p1, p1 + 1).first;
            ll v2 = st.calc(p2, p2 + 1).first;
            ll ans = min(righttotal(v2), lefttotal(v1));
            printf("%lld\n" , ans % MOD * calc_inv((i+1) - 2) % MOD);
        }
    }
}

int main(void) {
    solve();
}