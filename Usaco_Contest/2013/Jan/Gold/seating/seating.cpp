#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

struct segtree {
    struct seg {
        int cont;
        int pref;
        int suff;
        int size;

        seg(int c, int p, int s, int s2) {
            cont = c;
            pref = p;
            suff = s;
            size = s2;
        }
        seg() {;}
    };
    typedef struct seg Seg;

    Seg merge(Seg& a, Seg& b)
    {
        Seg c;
        c.cont = max(a.cont, max(b.cont, a.suff + b.pref));

        c.pref = a.pref;
        if (c.pref == a.size)
            c.pref += b.pref;

        c.suff = b.suff;
        if (c.suff == b.size)
            c.suff += a.suff;

        c.size = a.size + b.size;

        return c;
    }

    const Seg NEUTRAL = Seg(0, 0, 0, 0);
    const int NO_OP = INT_MAX;

    int size;
    vector<Seg> tree;
    vector<int> latest_op;

    Seg update_segment(Seg& a, int b, int len) {
        if (b == NO_OP) return a;
        return Seg(b * len, b * len, b * len, len);
    }
    int update_op(int a, int b) {
        if (b == NO_OP) return a;
        return b;
    }

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(size * 2, NEUTRAL);
        latest_op.assign(size * 2, NO_OP);
    }

    void apply_op(int& a, int b) {
        a = update_op(a, b);
    }
    void prop_seg(Seg& a, int b, int len) {
        a = update_segment(a, b, len);
    }

    void propagate(int x, int lx, int rx) {
        if (lx == rx - 1)
            return;
        // Go a step downwards
        int mid = (lx + rx) / 2;

        apply_op(latest_op[2 * x + 1], latest_op[x]);
        prop_seg(tree[2 * x + 1], latest_op[x], mid - lx);
        apply_op(latest_op[2 * x + 2], latest_op[x]);
        prop_seg(tree[2 * x + 2], latest_op[x], rx - mid);
        latest_op[x] = NO_OP;
    }

    void set(int l, int r, int v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || l >= rx)
            return;
        else if (l <= lx && rx <= r) {
            apply_op(latest_op[x], v);
            prop_seg(tree[x], v, rx - lx);
            return;
        }

        int mid = (lx + rx) / 2;
        set(l, r, v, 2 * x + 1, lx, mid);
        set(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int l, int r, int v) {
        set(l, r, v, 0, 0, size);
    }

    int find(int v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (tree[x].cont < v)
            return -1;
        if (lx == rx - 1)
            return lx;

        int mid = (lx + rx) / 2;
        int ans = find(v, 2 * x + 1, lx, mid);
        if (ans != -1)
            return ans;

        if (tree[2 * x + 1].suff + tree[2 * x + 2].pref >= v)
            return mid - tree[2 * x + 1].suff;

        return find(v, 2 * x + 2, mid, rx);
    }
    int find(int v) {
        return find(v, 0, 0, size);
    }
};

int n, m;
segtree st;

int main(void)
{
    freopen("seating.in", "r", stdin);
    freopen("seating.out", "w", stdout);

    scanf("%d %d", &n, &m);
    st.init(n);
    st.set(0, n, 1);

    char op;
    int ans = 0;
    while (m--) {
        scanf(" %c", &op);
        if (op == 'A') {
            int sz;
            scanf("%d", &sz);
            int initpos = st.find(sz);
            if (initpos == -1)
                ans++;
            else
                st.set(initpos, initpos + sz, 0);
        }
        else {
            int a, b;
            scanf("%d %d", &a, &b);
            a--;

            st.set(a, b, 1);
        }
    }

    printf("%d\n", ans);
}