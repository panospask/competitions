#include <bits/stdc++.h>

using namespace std;

struct segtree {

    int size = 1;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(size * 2);
    }

    void build(int n, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < n)
                tree[x] = 1;
            else
                tree[x] = 0;
            return;
        }

        int mid = (lx + rx) / 2;
        build(n, 2 * x + 1, lx, mid);
        build(n, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void build(int n) {
        build(n, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int find_kth_one(int k, int x, int lx, int rx) {
        if (tree[x] < k)
            return -1;
        else if (lx == rx - 1)
            return lx;

        int mid = (lx + rx) / 2;
        int ans = find_kth_one(k, 2 * x + 1, lx, mid);
        if (ans == -1)
            ans = find_kth_one(k - tree[2 * x + 1], 2 * x + 2, mid, rx);

        return ans;
    }
    int find_kth_one(int k) {
        return find_kth_one(k, 0, 0, size);
    }
};

int n;
vector<int> vals;
segtree st;

int main(void)
{
    scanf("%d", &n);
    vals.resize(n);
    st.init(n);
    st.build(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &vals[i]);

    int pos;
    for (int i = 0; i < n; i++) {
        scanf("%d", &pos);

        int rm = st.find_kth_one(pos);
        printf("%d ", vals[rm]);
        st.set(rm, 0);
    }
    printf("\n");
    return 0;
}