#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    int size;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size = 2 * size;
        }

        tree.assign(2 * size, 0);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            set(i, v, 2 * x + 1, lx, mid);
        }
        else {
            set(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        int c1 = sum(l, r, 2 * x + 1, lx, mid);
        int c2 = sum(l, r, 2 * x + 2, mid, rx);

        return c1 + c2;
    }
    int sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }

    int find_kth(int k, int x, int lx, int rx) {
        if (tree[x] < k) {
            return -1;
        }
        if (lx == rx - 1) {
            return lx;
        }

        int mid = (lx + rx) / 2;
        int ans = find_kth(k, 2 * x + 1, lx, mid);
        if (ans == -1) {
            ans = find_kth(k - tree[2  * x + 1], 2 * x + 2, mid, rx);
        }

        return ans;
    }
    int find_kth(int k) {
        return find_kth(k, 0, 0, size);
    }

    // Find next ace after i
    int nxt(int i) {
        int before = sum(0, i + 1);
        return find_kth(before + 1);
    }
};

int N, K;
vector<int> A;
vector<int> cnt;

vector<int> penalty;

SegTree st;

void solve(void) {
    scanf("%d %d", &N, &K);

    A.resize(N);
    cnt.assign(3 * N, 0);
    st.init(3 * N);
    penalty.assign(3 * N, 0);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        A[i]--;

        cnt[A[i]]++;
    }

    for (int v = 0; v < 3 * N; v++) {
        if (cnt[v] == 0) {
            st.set(v, 1);
        }
    }

    int ans = 0;
    for (int v = 2 * N; v >= 0; v--) {
        if (cnt[v] == 0) {
            continue;
        }

        int cur = 0;
        int p = v;
        while (cnt[v] > K) {
            // Move forward
            int nxt = st.nxt(p);

            // It'll take some operations
            cur += (nxt - p);
            cnt[v] += penalty[nxt];

            // Disable this and leave one element behind
            st.set(nxt, 0);
            cnt[v]--;
            p = nxt;
        }

        penalty[st.nxt(p)] += cnt[v] - 1;

        ans = max(ans, cur);
    }

    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}