#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18 + 5;

ll gcd(ll a, ll b)
{
    if (a < b) {
        swap(a, b);
    }
    if (a == INF) {
        return b;
    }

    if (b == 0) {
        return a;
    }
    else {
        return gcd(b, a % b);
    }
}

struct SegTree {
    int size;
    vector<ll> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, INF);
    }

    void build(vector<ll>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size()) {
                tree[x] = a[lx];
            }
            else {
                tree[x] = INF;
            }
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = gcd(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(vector<ll>& a) {
        build(a, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return INF;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        return gcd(calc(l, r, 2 * x + 1, lx, mid), calc(l, r, 2 * x + 2, mid, rx));
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N;
vector<ll> a;
SegTree st;

int main(void)
{
    scanf("%d", &N);

    a.resize(N);
    st.init(N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &a[i]);
    }
    st.build(a);
    
    int r = 1, ans = 1e6;
    for (int l = 0; l < N; l++) {
        while (r < N && st.calc(l, r) > 1) {
            r++;
        }

        if (st.calc(l, r) == 1) {
            ans = min(ans, r - l);
        }
    }

    ans = ans == 1e6 ? -1 : ans;
    printf("%d\n", ans);

    return 0;
}