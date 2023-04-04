#include <bits/stdc++.h>

using namespace std;

int NULL_ELEMENT = INT_MIN;

struct segtree {

    int size = 1;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            // Bottom layer     
            if (lx < a.size())
                tree[x] = a[lx];
            else 
                tree[x] = NULL_ELEMENT;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            // The i-th pos is before the middle of the segment
            set(i, v, 2 * x + 1, lx, mid);
        }
        else {
            // The i-th pos is after the middle of the segment
            set(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int find_pos(int v, int l, int x, int lx, int rx) {
        if (tree[x] < v)
            return -1;
        if (rx <= l)
            return -1;


        if (lx == rx - 1) {
            return lx;
        }

        int mid = (lx + rx) / 2;      
        int ans = find_pos(v, l, 2 * x + 1, lx, mid);
        if (ans == -1)
            ans = find_pos(v, l, 2 * x + 2, mid, rx);

        return ans;
    }
    int find_pos(int v, int l) {
        return find_pos(v, l, 0, 0, size);
    }
};

int n, m;
vector<int> a;
segtree st;

int main(void)
{
    scanf("%d %d", &n, &m);
    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    st.init(n);
    st.build(a);

    while (m--) {
        int op;
        scanf("%d", &op);
        
        if (op == 1) {
            int i, v;
            scanf("%d %d", &i, &v);
            st.set(i, v);
        }
        else {
            int x;
            scanf("%d", &x);
            printf("%d\n", st.find_pos(x, 0));
        }
    }

    return 0;
}