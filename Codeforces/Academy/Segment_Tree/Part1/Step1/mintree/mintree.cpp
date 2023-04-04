#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

struct segtree {
    
    int size = 4 * MAXN;
    vector<int> values;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        values.resize(size * 2);
    }

    void build(vector<int>& a, int x, int l_x, int r_x) {
        if (l_x == r_x - 1) {
            if (l_x < (int)a.size())
                values[x] = a[l_x];
            else 
                values[x] = INT_MAX;
            
            return;
        }

        int mid = (l_x + r_x) / 2;
        build(a, 2 * x + 1, l_x, mid);
        build(a, 2 * x + 2, mid, r_x);

        values[x] = min(values[2 * x+ 1], values[2 * x + 2]);
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int l_x, int r_x) {
        if (l_x == r_x - 1) {
            values[x] = v;
            return;
        }

        int mid = (l_x + r_x) / 2;
        if (i < mid) 
            set(i, v, 2 * x + 1, l_x, mid);
        else 
            set(i, v, 2 * x + 2, mid, r_x);

        values[x] = min(values[2 * x+ 1], values[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int query(int l, int r, int x, int l_x, int r_x) {
        if (l <= l_x && r_x <= r) {
            // Fully contained
            return values[x];
        }
        else if (l >= r_x || l_x >= r) {
            // Disjoint segments
            return INT_MAX;
        }

        int mid = (l_x + r_x) / 2;
        int m1 = query(l, r, 2 * x + 1, l_x, mid);
        int m2 = query(l, r, 2 * x + 2, mid, r_x);
        return min(m1, m2);
    }
    int query(int l, int r) {
        return query(l, r, 0, 0, size);
    }
};

int n, m;

int main(void)
{
    scanf("%d %d", &n, &m);
    segtree st;

    vector<int> a(n);
    st.init(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        st.set(i, a[i]);
    }
    
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
            cout << st.query(l, r) << endl;
        }
    }
}