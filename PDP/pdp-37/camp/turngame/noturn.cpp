#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    int size;
    vector<ll> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, 0);
    }

    void set(int i, ll v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = max(tree[x], v);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            set(i, v, 2 * x + 1, lx, mid);
        }
        else {
            set(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ll c1 = calc(l, r, 2 * x + 1, lx, mid);
        ll c2 = calc(l, r, 2 * x + 2, mid, rx);

        return max(c1, c2);
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N;
ll C;

vector<int> A;
vector<int> cords;

SegTree st;

int find(int v) {
    return lower_bound(cords.begin(), cords.end(), v) - cords.begin();
}

int main(void) {
    scanf("%d %lld", &N, &C);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        cords.push_back(A[i]);
    }
    sort(cords.begin(), cords.end());
    cords.resize(unique(cords.begin(), cords.end()) - cords.begin());

    ll ans = 0;
    
    st.init(N);
    for (int i = 0; i < N; i++) {
        ll prv = st.calc(0, find(A[i]));
        ans = max(ans, prv + A[i]);

        st.set(find(A[i]), prv + A[i]);
    }

    st.init(N);
    for (int i = N - 1; i >= 0; i--) {
        ll prv = st.calc(0, find(A[i]));
        ans = max(ans, prv + A[i]);

        st.set(find(A[i]), prv + A[i]);
    }

    printf("%lld\n", ans);

    return 0;
}