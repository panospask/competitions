#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

struct SegTree {
    int size;

    vector<int> tree;
    vector<int> lazy;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, 0);
        lazy.assign(2 * size, 0);
    }

    void propagate(int x) {
        tree[2 * x + 1] = tree[2 * x + 1] + lazy[x];
        tree[2 * x + 2] = tree[2 * x + 2] + lazy[x];
        lazy[2 * x + 1] = lazy[2 * x + 1] + lazy[x];
        lazy[2 * x + 2] = lazy[2 * x + 2] + lazy[x];

        lazy[x] = 0;
    }

    void add(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        if (l <= lx && rx <= r) {
            tree[x] += v;
            lazy[x] += v;
            return;
        }

        propagate(x);
        int mid = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, mid);
        add(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int l, int r, int v) {
        add(l, r, v, 0, 0, size);
    }

    int worse(void) {
        return tree[0];
    }
};

int N, M, Q;
vector<int> A;
vector<vector<int>> B;
SegTree st;

int score(int v) {
    return v < A[0];
}

int main(void) {
    scanf("%d %d %d", &N, &M, &Q);

    A.resize(N);
    B.assign(M + 1, vector<int>());
    st.init(M + 1);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);

        st.add(0, M + 1, score(A[i]));
    }

    int sum = 0;
    for (int i = 1; i <= M; i++) {
        int R;
        scanf("%d", &R);
        B[i].resize(R);
        sum += R;
        st.add(i - 1, i, -sum);
        for (int j = 0; j < R; j++) {
            scanf("%d", &B[i][j]);
            st.add(i, M + 1, score(B[i][j]));
        }
    }

    while (Q--) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        y--;

        st.add(x, M + 1, -score(B[x][y]));
        B[x][y] = z;
        st.add(x, M + 1, score(z));

        int ans = st.worse() >= 0;
        printf("%d\n", ans);
    }
}