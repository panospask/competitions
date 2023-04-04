#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int n;
int vals[MAXN + 2];

struct segtree {

    int size = 1;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
    }

    void build(int* a, int ind, int lind, int rind) {
        if (lind == rind - 1) {
            if (lind < n)
                tree[ind] = a[lind];
            else 
                tree[ind] = 0;

            return;
        }

        int mid = (lind + rind) / 2;
        build(a, 2 * ind + 1, lind, mid);
        build(a, 2 * ind + 2, mid, rind);

        tree[ind] = tree[2 * ind + 1] + tree[2 * ind + 2];
    }
    void build(int* a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int ind, int lind, int rind) {
        if (lind == rind - 1) {
            tree[ind] = v;
            return;
        }

        int mid = (lind + rind) / 2;
        if (i < mid)
            set(i, v, 2 * ind + 1, lind, mid);
        else 
            set(i, v, 2 * ind + 2, mid, rind);

        tree[ind] = tree[2 * ind + 1] + tree[2 * ind + 2];
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    // Find k-th one FROM THE END OF THE ARRAY
    int find_one(int k, int ind, int lind, int rind) {
        if (lind == rind - 1)
            return lind;
        
        int mid = (lind + rind) / 2;
        if (tree[2 * ind + 2] > k) // 0 based counting
            return find_one(k, 2 * ind + 2, mid, rind);
        else 
            return find_one(k - tree[2 * ind + 2], 2 * ind + 1, lind, mid);
    }
    int find_one(int k) {
        return find_one(k, 0, 0, size);
    }
};

segtree st;
int ans[MAXN + 2];

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &vals[i]);

    int starting[MAXN + 2];
    for (int i = 0; i < n; i++)
        starting[i] = 1; // All places are empty
    st.init(n);
    st.build(starting);
    // Go from back to front, the last value of the array will always have the position of the k-th one from the right

    for (int i = n - 1; i >= 0; i--) {
        int value = st.find_one(vals[i]);

        ans[i] = value;

        // Set the current position to 0, it is used
        st.set(value, 0);
    }

    for (int i = 0; i < n; i++) 
        printf("%d ", ans[i] + 1);

    return 0;
}