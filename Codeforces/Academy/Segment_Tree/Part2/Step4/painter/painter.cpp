#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair

using namespace std;

const int MAXC = (int)1e5 * 5;

typedef pair<int, int> pi;

struct SegTree {
    struct Segment {
        int num;
        int len;
        bool joinleft;
        bool joinright;
    };

    const Segment NEUTRAL = {0, 0, 0, 0};

    Segment merge(Segment& a, Segment& b) {
        Segment c;
        c.len = a.len + b.len;
        c.num = a.num + b.num;

        if (a.joinright && b.joinleft) {
            c.num--;
            c.len++;
        }

        c.joinleft = a.joinleft;
        c.joinright = b.joinright;

        return c;
    }

    const int NO_OP = 0;

    void make_mod(Segment& a, int op, int len) {
        if (op == NO_OP)
            return;

        if (op == 1) {
            // Make black
            a.joinleft = a.joinright = true;
            a.len = len;
            a.num = 1;
        }
        else {
            a = NEUTRAL;
        }
    }
    void make_mod(int& a, int b) {
        a = (b == NO_OP ? a : b);
    }

    int size;
    vector<Segment> tree;
    vector<int> operations;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, NEUTRAL);
        operations.assign(2 * size, NO_OP);
    }

    void propagate(int x, int lx, int rx) {
        int mid = (lx + rx) / 2;

        make_mod(tree[2 * x + 1], operations[x], mid - lx);
        make_mod(tree[2 * x + 2], operations[x], rx - mid - 1);
        make_mod(operations[2 * x + 1], operations[x]);
        make_mod(operations[2 * x + 2], operations[x]);

        operations[x] = NO_OP;
    }

    void modify(int l, int r, int op, int x, int lx, int rx) {
        if (l > rx || lx > r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            make_mod(tree[x], op, rx - lx);
            make_mod(operations[x], op);
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        modify(l, r, op, 2 * x + 1, lx, mid);
        modify(l, r, op, 2 * x + 2, mid + 1, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void make_white(int l, int r) {
        modify(l, r, 2, 0, 0, size - 1);
    }
    void make_black(int l, int r) {
        modify(l, r, 1, 0, 0, size - 1);
    }

    pi total(void) {
        return mp(tree[0].num, tree[0].len);
    }
};

int n, m;
SegTree st;

int main(void)
{
    scanf("%d", &n);

    st.init(2 * MAXC);
    while (n--) {
        int x, l;
        char c;
        scanf(" %c %d %d", &c, &x, &l);

        x += MAXC;

        if (c == 'W') {
            st.make_white(x, x + l);
        }
        else {
            st.make_black(x, x + l);
        }

        pi ans = st.total();
        printf("%d %d\n", ans.f, ans.s);
    }

    return 0;
}