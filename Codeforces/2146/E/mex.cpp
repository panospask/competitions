#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    int size;

    vector<int> operations;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size = 2 * size;
        }

        tree.assign(2 * size, 0);
        operations.assign(2 * size, 0);
    }

    void propagate(int x) {
        tree[2 * x + 1] += operations[x];
        tree[2 * x + 2] += operations[x];
        operations[2 * x + 1] += operations[x];
        operations[2 * x + 2] += operations[x];
        operations[x] = 0;
    }

    void add(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            operations[x] += v;
            tree[x] += v;
            return;
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, mid);
        add(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int l, int r, int v) {
        add(l, r, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        int c1 = calc(l, r, 2 * x + 1, lx, mid);
        int c2 = calc(l, r, 2 * x + 2, mid, rx);

        return max(c1, c2);
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }

    void nullify(int i) {
        add(i, i + 1, -calc(i, i + 1));
    }
};

int N;
SegTree st;
vector<int> A;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    st.init(N + 1);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < N; i++) {
        st.nullify(A[i]);
        st.add(0, A[i], 1);

        printf("%d ", st.calc(0, N + 1));
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}