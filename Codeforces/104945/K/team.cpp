#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    int size;
    vector<int> tree;

    void build(int x, int lx, int rx, int N) {
        if (lx == rx - 1) {
            if (lx < N) {
                tree[x] = 1;
            }
            return;
        }

        int mid = (lx + rx) / 2;
        build(2 * x + 1, lx, mid, N);
        build(2 * x + 2, mid, rx, N);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, 0);
        build(0, 0, size, N);
    }

    int kth(int k, int x, int lx, int rx) {
        if (tree[x] < k) {
            return -1;
        }
        if (lx == rx - 1) {
            tree[x] = 0;
            return lx;
        }

        int mid = (lx + rx) / 2;
        int ans = kth(k, 2 * x + 1, lx, mid);
        if (ans == -1) {
            ans = kth(k - tree[2 * x + 1], 2 * x + 2, mid, rx);
        }

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];

        return ans;
    }
    int kth(int k) {
        return kth(k, 0, 0, size);
    }
};

int N;
SegTree st;
vector<int> A, B;

int main(void) {
    scanf("%d", &N);
    st.init(N);
    A.resize(N / 2);
    B.resize(N / 2);

    for (int i = 0; i < N / 2; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N / 2; i++) {
        scanf("%d", &B[i]);
    }

    vector<int> ans1(N / 2), ans2(N / 2);
    for (int i = 0; i < N / 2; i++) {
        ans1[i] = st.kth(A[i]) + 1;
        ans2[i] = st.kth(B[i]) + 1;
    }

    for (int i = 0; i < N / 2; i++) {
        printf("%d ", ans1[i]);
    }
    printf("\n");
    for (int i = 0; i < N / 2; i++) {
        printf("%d ", ans2[i]);
    }
    printf("\n");
}