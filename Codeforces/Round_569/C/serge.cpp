#include <bits/stdc++.h>

using namespace std;

const int MAXC = 1e6;

struct SegTree {
    struct Node {
        int total;
        int max;
    };
    const Node NEUTRAL = {0, 0};

    Node merge(Node& a, Node& b) {
        return {a.total + b.total, max(a.max, a.total + b.max)};
    };

    int size;
    vector<Node> tree;

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size()) {
                tree[x].total = a[lx];
                tree[x].max = max(0, a[lx]);
            }

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

        tree.assign(2 * size, NEUTRAL);
        build(a, 0, 0, size);
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x].total += v;
            tree[x].max = max(tree[x].total, 0);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            add(i, v, 2 * x + 1, lx, mid);
        else
            add(i, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    int first_over(int v, int x, int lx, int rx) {
        if (tree[x].max < v) {
            return -1;
        }
        if (lx == rx - 1) {
            return lx;
        }

        int mid = (lx + rx) / 2;
        int res = first_over(v, 2 * x + 1, lx, mid);
        if (res == -1)
            res = first_over(v - tree[2 * x + 1].total, 2 * x + 2, mid, rx);

        return res;
    }
    int first_over(int v) {
        return first_over(v, 0, 0, size);
    }
};

int n, m, q;
vector<int> a;
vector<int> b;
vector<int> frq;
SegTree st;

int main(void)
{
    scanf("%d %d", &n, &m);
    a.resize(n);
    b.resize(m);
    frq.resize(MAXC);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        frq[MAXC - a[i]]++;
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
        frq[MAXC - b[i]]--;
    }

    scanf("%d", &q);
    st.init(MAXC, frq);

    while (q--) {
        int op, i, x;
        scanf("%d %d %d", &op, &i, &x);
        i--;

        if (op == 1) {
            st.add(MAXC - a[i], -1);
            a[i] = x;
            st.add(MAXC - a[i], +1);
        }
        else {
            st.add(MAXC - b[i], +1);
            b[i] = x;
            st.add(MAXC - b[i], -1);
        }

        int ans = st.first_over(1);
        if (ans != -1)
            ans = MAXC - ans;

        printf("%d\n", ans);
    }

    return 0;
}