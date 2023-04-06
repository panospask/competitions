#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

struct matrix {
    int a, b, c, d;

    matrix(void) {;}
    matrix(int x, int y, int z, int w) {
        a = x;
        b = y;
        c = z;
        d = w;
    }
};
typedef struct matrix Matrix;

int R, n, m;
Matrix a[MAXN + 2];

Matrix NULL_ELEMENT = Matrix(1, 0, 0, 1);

Matrix mult(Matrix x, Matrix y) 
{
    Matrix c;
    c.a = (x.a * y.a + x.b * y.c) % R;
    c.b = (x.a * y.b + x.b * y.d) % R;
    c.c = (x.c * y.a + x.d * y.c) % R;
    c.d = (x.c * y.b + x.d * y.d) % R;

    return c;
}

struct segtree {

    int size = 1;
    vector<Matrix> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;
        
        tree.resize(2 * size);
    }

    void build(Matrix* a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < n)     
                tree[x] = a[lx];
            else 
                tree[x] = NULL_ELEMENT;
            
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = mult(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(Matrix* a) {
        build(a, 0, 0, size);
    }

    Matrix calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return NULL_ELEMENT;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        auto m1 = calc(l, r, 2 * x + 1, lx, mid);
        auto m2 = calc(l, r, 2 * x + 2, mid, rx);

        return mult(m1, m2);
    }
    Matrix calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int main(void)
{
    scanf("%d %d %d", &R, &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &a[i].a, &a[i].b, &a[i].c, &a[i].d);
    }

    segtree st;
    st.init(n);
    st.build(a);

    while (m--) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--;

        auto ans = st.calc(l, r);

        printf("%d %d\n%d %d\n\n", ans.a, ans.b, ans.c, ans.d);
    }

    return 0;
}