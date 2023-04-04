#include <bits/stdc++.h>

using namespace std;

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
            if (lx < a.size()) 
                tree[x] = a[lx];
            else 
                tree[x] = 0;
            
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void change(int i, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = !tree[x];
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            change(i, 2 * x + 1, lx, mid);
        else 
            change(i, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void change(int i) {
        return change(i, 0, 0, size);
    }

    int find(int k, int x, int lx, int rx) {
        if (lx == rx - 1)
            return lx;

        int mid = (lx + rx) / 2;
        if (tree[2 * x + 1] > k)
            return find(k, 2 * x + 1, lx, mid);
        else 
            return find(k - tree[2 * x + 1], 2 * x + 2, mid, rx);
    }
    int find(int k) {
        return find(k, 0, 0, size);
    }
};

vector<int> a;
int n, m;

int main(void)
{
    scanf("%d %d", &n, &m);
    a.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    segtree st;
    st.init(n);
    st.build(a);

    while (m--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int i;
            scanf("%d", &i);
            st.change(i);
        }
        else {
            int k;
            scanf("%d", &k);
            printf("%d\n", st.find(k));
        }
    }

    return 0;
}