#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll NO_ANS = -1e12;
const int GAME = 1;
const int MATH = 0;
const int NOTHING = -1;
const int NO_TIME = INT_MIN;

struct SegTree {
    struct Node {
        // Variables irrespective of the type of program
        int len = 0;
        ll total = 0;
        ll opt_pref = NO_ANS, opt_suff = NO_ANS;
        ll max = NO_ANS;

        // Variables depending on the type of program
        // What are the first and last programs
        int pref_v = NOTHING, suff_v = NOTHING;
        // And their respective NON-EMPTY streaks of same_program
        ll pref_streak = NO_ANS, suff_streak = NO_ANS;
        // The biggest possible number of elements in each
        int pref_ttl = 0, suff_ttl = 0;

        int streak[2] = {0, 0};
        ll ans[2] = {NO_ANS, NO_ANS};
    };
    Node NEUTRAL;

    struct Operation {
        int game;
        ll time;
    };
    const Operation NO_OP = {NOTHING, NO_TIME};

    void make_mod(Node& a, Operation op) {
        if (op.game != NOTHING) {
            a.streak[op.game] = a.len;
            a.streak[!op.game] = 0;
            a.ans[op.game] = a.max;
            a.ans[!op.game] = NO_ANS;

            a.pref_v = a.suff_v = op.game;
            a.pref_ttl = a.suff_ttl = a.len;
            a.pref_streak = a.opt_pref;
            a.suff_streak = a.opt_suff;
        }
        if (op.time != NO_TIME) {
            a.total = op.time * a.len;

            if (op.time < 0) {
                a.opt_suff = a.opt_pref = a.max = op.time;
            }
            else {
                a.opt_suff = a.opt_pref = a.max = op.time * a.len;
            }

            // Change program dependent variables
            if (op.time < 0) {
                a.suff_streak = a.pref_streak = op.time;
            }
            else {
                a.suff_streak = op.time * a.suff_ttl;
                a.pref_streak = op.time * a.pref_ttl;
            }

            for (int i = 0; i < 2; i++)
                if (a.streak[i]) {
                    a.ans[i] = (op.time < 0 ? op.time : op.time * a.streak[i]);
                }
        }
    }

    void make_mod(Operation& a, Operation b) {
        if (b.game != NOTHING)
            a.game = b.game;
        if (b.time != NO_TIME)
            a.time = b.time;
    }

    Node create(int a) {
        Node c;
        c.len = 1;

        Operation e = {GAME, a};
        make_mod(c, e);

        return c;
    }

    Node merge(Node a, Node b) {
        Node c;

        c.len = a.len + b.len;

        c.total = a.total + b.total;
        c.max = max(max(a.max, b.max), a.opt_suff + b.opt_pref);
        c.opt_pref = max(a.opt_pref, a.total + b.opt_pref);
        c.opt_suff = max(b.opt_suff, b.total + a.opt_suff);

        c.ans[GAME] = max(a.ans[GAME], b.ans[GAME]);
        c.ans[MATH] = max(a.ans[MATH], b.ans[MATH]);
        c.streak[GAME] = max(a.streak[GAME], b.streak[GAME]);
        c.streak[MATH] = max(a.streak[MATH], b.streak[MATH]);

        c.pref_v = a.pref_v;
        c.pref_streak = a.pref_streak;
        c.pref_ttl = a.pref_ttl;

        c.suff_v = b.suff_v;
        c.suff_streak = b.suff_streak;
        c.suff_ttl = b.suff_ttl;

        if (a.suff_v == b.pref_v) {
            c.ans[a.suff_v] = max(c.ans[a.suff_v], a.suff_streak + b.pref_streak);
            c.streak[a.suff_v] = max(c.streak[a.suff_v], a.suff_ttl + b.pref_ttl);

            if (a.pref_ttl == a.len) {
                c.pref_streak = max(c.pref_streak, a.total + b.pref_streak);
                c.pref_ttl += b.pref_ttl;
            }
            if (b.pref_ttl == b.len) {
                c.suff_streak = max(c.suff_streak, b.total + a.suff_streak);
                c.suff_ttl += a.suff_ttl;
            }
        }

        return c;
    }

    int size;
    vector<Node> tree;
    vector<Operation> operations;

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = create(a[lx]);

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
        operations.assign(2 * size, NO_OP);

        build(a, 0, 0, size);
    }

    void propagate(int x, int lx, int rx) {
        make_mod(tree[2 * x + 1], operations[x]);
        make_mod(tree[2 * x + 2], operations[x]);
        make_mod(operations[2 * x + 1], operations[x]);
        make_mod(operations[2 * x + 2], operations[x]);

        operations[x] = NO_OP;
        return;
    }

    void modify(int l, int r, Operation v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            make_mod(tree[x], v);
            make_mod(operations[x], v);
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
        return;
    }
    void change_game(int l, int r, int g) {
        Operation v = {g, NO_TIME};
        modify(l, r, v, 0, 0, size);
    }
    void change_time(int l, int r, int t) {
        Operation v = {NOTHING, t};
        modify(l, r, v, 0, 0, size);
    }

    Node calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        return merge(calc(l, r, 2 * x + 1, lx, mid), calc(l, r, 2 * x + 2, mid, rx));
    }
    void get_time(int l, int r, int game) {
        Node v = calc(l, r, 0, 0, size);

        if (v.ans[game] != NO_ANS)
            printf("%lld\n", v.ans[game]);
        else
            printf("breaks galore\n");
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
            int l, r;
            scanf("%d %d", &l, &r);
            l--;

            st.change_game(l, r, GAME);
        }
        else if (op == 2) {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;

            st.change_game(l, r, MATH);
        }
        else if (op == 3) {
            int l, r, x;
            scanf("%d %d %d", &l, &r, &x);
            l--;

            st.change_time(l, r, x);
        }
        else if (op == 4) {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;

            st.get_time(l, r, GAME);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;

            st.get_time(l, r, MATH);
        }
    }

    return 0;
}