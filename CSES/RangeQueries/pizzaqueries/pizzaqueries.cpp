#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll IMP = 1e15;

struct SegTree {
    struct Block {
        int len;
        ll price_left;
        ll price_right;
    };
    const Block NEUTRAL = {1, IMP, IMP};

    Block create(int p) {
        return {1, p, p};
    }

    Block merge(Block& a, Block& b) {
        Block c;
        c.len = a.len + b.len;
        c.price_left = min(a.price_left, b.price_left + a.len);
        c.price_right = min(b.price_right, a.price_right + b.len);

        return c;
    }

    int size;
    vector<Block> tree;

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = create(a[lx]);
            else
                tree[x] = NEUTRAL;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void init(int n, vector<int>& a) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = create(v);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    ll get(int i, int x, int lx, int rx) {
        if (lx == rx - 1) {
            return tree[x].price_left;
        }

        int mid = (lx +rx) / 2;
        if (i < mid) {
            return min(get(i, 2 * x + 1, lx, mid), mid - i + tree[2 * x + 2].price_left);
        }
        else {
            return min(get(i, 2 * x + 2, mid, rx), i - mid + 1 + tree[2 * x + 1].price_right);
        }
    }
    ll get(int i) {
        return get(i, 0, 0, size);
    }
};

int n, q;
vector<int> a;
SegTree st;

int main(void)
{
    scanf("%d %d", &n, &q);
    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    st.init(n, a);
    while (q--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int i, v;
            scanf("%d %d", &i, &v);
            i--;

            st.set(i, v);
        }
        else {
            int i;
            scanf("%d", &i);
            i--;

            printf("%lld\n", st.get(i));
        }
    }

    return 0;
}