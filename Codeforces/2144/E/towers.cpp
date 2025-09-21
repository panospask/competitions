#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const int MOD = 998244353;

struct segtree {

    int size = 1;
    vector<long long> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(size * 2);
    }

    void build(vector<int>&a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = a[lx];
            else
                tree[x] = 0;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            add(i, v, 2 * x + 1, lx, mid);
        else
            add(i, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    long long sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return 0;
        }
        if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        auto s1 = sum(l, r, 2 * x + 1, lx, mid);
        auto s2 = sum(l, r, 2 * x + 2, mid, rx);

        return s1 + s2;
    }
    long long sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};

int N;
vector<int> a;

vector<int> l;
vector<int> r;

bool cmp(int i, int j) {
    if (a[i] == a[j]) {
        return i < j;
    }
    return a[i] < a[j];
}

void calculate(vector<ll>& res) {
    vector<int> order;
    for (int i = 0; i < N; i++) {
        order.pb(i);
    }
    sort(order.begin(), order.end(), cmp);

    segtree st;

    vector<int> s;
    s.pb(a[0]);
    for (int i = 0; i < N; i++) {
        if (a[i] > s.back()) {
            s.pb(a[i]);
        }
    }

    // We need to follow s
    st.init(N);
    int p = 0;
    vector<int> cur;
    vector<int> prv;
    vector<int> inter;
    for (int i = 0; i < s.size(); i++) {
        // First find inter
        while (a[order[p]] < s[i]) {
            inter.pb(order[p]);
            p++;
        }

        while (p < N && a[order[p]] == s[i]) {
            cur.pb(order[p]);
            p++;
        }

        int q = 0;
        int r = 0;
        ll ways = 0;
        for (auto j : cur) {
            while (q < inter.size() || r < prv.size()) {
                if (r == prv.size() || (q != inter.size() && inter[q] < prv[r])) {
                    if (inter[q] >= j) {
                        break;
                    }
                    ways = (ways * 2) % MOD;
                    q++;
                }
                else {
                    if (prv[r] >= j) {
                        break;
                    }
                    ways++;
                    r++;
                }
            }

            if (i == 0) {
                res[j] = 1;
            }
            else {
                res[j] = ways;
            }
        }

        
        q = 0;
        r = 0;
        while (q < inter.size()) {
            st.add(inter[q], 1);
            q++;
        }
        while (r < prv.size()) {
            st.add(prv[r], 1);
            r++;
        }
        swap(cur, prv);
        cur.clear();
        inter.clear();
    }
}

void solve(void) {
    scanf("%d", &N);

    a.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    vector<ll> r1(N), r2(N);
    calculate(r1);
    reverse(a.begin(), a.end());
    calculate(r2);
    reverse(a.begin(), a.end());
    reverse(r2.begin(), r2.end());

    int mx = 0;
    for (int i = 0; i < N; i++) {
        mx = max(mx, a[i]);
    }

    ll ans = 0;

    ll prf = 1;
    for (int i = 0; i < N; i++) {
        if (a[i] == mx) {
            prf = prf * r1[i] % MOD;
            ans = (ans + prf *r2[i] % MOD) % MOD;
        }
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}