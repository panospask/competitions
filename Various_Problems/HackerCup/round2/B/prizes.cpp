#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int INF = 1e9 + 1;

struct SegTree {

    int size;
    vector<ll> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, 0);
    }

    void add(int l, int r, int v, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, mid);
        add(l, r, v, 2 * x + 2, mid, rx);

        return;
    }
    void add(int l, int r, int v) {
        add(l, r, v, 0, 0, size);
    }

    ll get(int i, int x, int lx, int rx) {
        if (lx == rx - 1) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ll res;
        if (i < mid)
            res = get(i, 2 * x + 1, lx, mid);
        else
            res = get(i, 2 * x + 2, mid, rx);

        return res + tree[x];
    }
    ll get(int i) {
        return get(i, 0, 0, size);
    }
};

int N, M;
vector<int> A, B;
SegTree st;

int last(int v) {
    int l = -1;
    int r = M;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (st.get(mid) >= v) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    return l;
}

// Can we give first x at least 1 ?
bool test(int X) {
    // Current position
    while (X < N && A[X - 1] == A[X]) {
        X++;
    }

    st.init(M);
    for (int i = 0; i < M; i++) {
        st.add(i, i + 1, B[i]);
    }

    // We now only care about people in [0, X)
    int p = 0;
    int cutoff = X;

    int cnt = 1;
    for (int i = 1; i < cutoff; i++) {
        if (A[i] != A[i - 1]) {
            cnt++;
        }
    }

    for (int i = 0; i < cutoff; i++) {
        if (i && A[i] != A[i - 1]) {
            cnt--;
        }

        if (cnt > M) {
            return false;
        }

        int v = st.get(cnt - 1);
        if (v == 0) {
            return false;
        }

        int a1 = last(v + 1);
        int a2 = last(v);
        int wanted_final = cnt - (a1 + 1);

        st.add(0, a1 + 1, -1);
        st.add(a2 - wanted_final + 1, a2 + 1, -1);
    }

    return true;
}

void solve(void) {
    scanf("%d %d", &N, &M);

    A.resize(N);
    B.resize(M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &B[i]);
    }

    sort(A.rbegin(), A.rend());
    sort(B.rbegin(), B.rend());

    int l = 0;
    int r = N + 1;

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (test(mid)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    printf("%d\n", l);
}

int main(void) {
    int t;
    scanf("%d", &t);
    
    for (int i = 0; i < t; i++) {
        printf("Case #%d: ", i + 1);
        solve();
    }

    return 0;
}