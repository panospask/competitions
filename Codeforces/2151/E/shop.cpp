#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

struct SegTree {
    int size;
    vector<ll> tree;

    vector<ll> setop;
    vector<ll> addop;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, -INF);
        setop.assign(2 * size, -INF);
        addop.assign(2 * size, 0);
    }

    void propagate(int x) {
        if (setop[x] != -INF) {
            tree[2 * x + 1] = tree[2 * x + 2] = setop[x];
            setop[2 * x + 1] = setop[2 * x + 2] = setop[x];
            addop[2 * x + 1] = addop[2 * x + 2] = 0;
            setop[x] = -INF;
        }
        if (addop[x] != 0) {
            tree[2 * x + 1] += addop[x];
            tree[2 * x + 2] += addop[x];
            addop[2 * x + 1] += addop[x];
            addop[2 * x + 2] += addop[x];
            addop[x] = 0;
        }
    }

    void modify(int l, int r, ll v, bool s, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            if (s) {
                tree[x] = setop[x] = v;
                addop[x] = 0;
            }
            else {
                tree[x] += v;
                addop[x] += v;
            }

            return;
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        modify(l, r, v, s, 2 * x + 1, lx, mid);
        modify(l, r, v, s, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void modify(int l, int r, ll v, bool s) {
        modify(l, r, v, s, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return -INF;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        return max(calc(l, r, 2 * x + 1, lx, mid), calc(l, r, 2 * x + 2, mid, rx));
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N;
vector<int> v, a, b;

vector<int> inv;

SegTree st;

void solve(void) {
    scanf("%d", &N);

    v.resize(N);
    a.resize(N);
    inv.resize(N);
    st.init(N + 1);

    for (int i = 0; i < N; i++) {
        scanf("%d", &v[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        a[i]--;
    }
    for (int i = 0; i < N; i++) {
        int b;
        scanf("%d", &b);
        b--;

        inv[b] = i + 1;
    }

    for (int i = 0; i <= N; i++) {
        st.modify(i, i + 1, 0, 1);
    }

    for (int i = 0; i < N; i++) {
        st.modify(0, inv[a[i]], v[a[i]], 0);

        int p = inv[a[i]];
        ll t = st.calc(p - 1, p);

        int l = p - 1;
        int r = N + 1;
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            if (st.calc(mid, mid + 1) < t) {
                l = mid;
            }
            else {
                r = mid;
            }
        } 

        st.modify(p, r, t, 1);
    }

    printf("%lld\n", st.calc(N, N + 1));
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}