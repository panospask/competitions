#include <bits/stdc++.h>

using namespace std;

struct element {
    int m, c;

    element(void) {;}
    element(int a, int b) {
        m = a;
        c = b;
    }
};
typedef struct element Element;

Element NULL_ELEMENT = Element(INT_MAX, 0);

Element merge(Element a, Element b) {
    if (a.m < b.m)
        return a;
    else if (b.m < a.m)
        return b;
    else 
        return Element(a.m, a.c + b.c);
}

struct segtree {

    int size;
    vector<Element> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        // The leaves of the tree are the firt power of two bigger than n => the whole tree has twice the nodes
        tree.resize(2 * size);
    }

    void build(vector<int>& a, int x, int l_x, int r_x) {
        if (l_x == r_x - 1) {
            if (l_x < a.size()) {
                tree[x] = Element(a[l_x], 1);
            }
            else 
                tree[x] = NULL_ELEMENT;

            return;
        }

        int mid = (l_x + r_x) / 2;
        build(a, 2 * x + 1, l_x, mid);
        build(a, 2 * x + 2, mid, r_x);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int l_x, int r_x) {
        if (l_x == r_x - 1) {
            tree[x] = Element(v, 1);
            return;
        }

        int mid = (l_x + r_x) / 2;
        if (i < mid) 
            set(i, v, 2 * x + 1, l_x, mid);
        else 
            set(i, v, 2 * x + 2, mid, r_x);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    Element query(int l, int r, int x, int l_x, int r_x) {
        if (l >= r_x || l_x >= r) {
            // Disjoint sets
            return NULL_ELEMENT;
        }
        else if (l <= l_x && r_x <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (l_x + r_x) / 2;
        Element q1 = query(l, r, 2 * x + 1, l_x, mid);
        Element q2 = query(l, r, 2 * x + 2, mid, r_x);
        return merge(q1, q2);
    }
    Element query(int l, int r) {
        return query(l, r, 0, 0, size);
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

    for (int q = 0; q < m; q++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int i, v;
            scanf("%d %d", &i, &v);
            st.set(i, v);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);
            auto ans = st.query(l, r);
            printf("%d %d\n", ans.m, ans.c);
        }
    }
    return 0;
}