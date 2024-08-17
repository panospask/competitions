#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

struct SegTree {
    struct Node {
        /* ans[l][r]:
         * The maximum answer for this segment
         *
         * l and r are boolean variables denoting if we include the leftmost and rightmost elements
         * respectively
         */
        vector<vector<ll>> ans;

        vector<ll> sign;

        Node(void) {
            ans.assign(2, vector<ll>(2, 0));
            sign.assign(2, 0);
        }
    };

    Node DEFAULT;
    int size;
    vector<Node> tree;

    Node merge(const Node& a, const Node& b)
    {
        Node res;

        res.sign[0] = a.sign[0];
        res.sign[1] = b.sign[1];
        if (a.sign[1] == b.sign[0] || a.sign[1] == 0 || b.sign[0] == 0) {
            // We can merge

            for (int l = 0; l < 2; l++) {
                for (int r = 0; r < 2; r++) {
                    res.ans[l][r] = a.ans[l][1] + b.ans[1][r];
                }
            }
        }
        else {
            for (int l = 0; l < 2; l++) {
                for (int r = 0; r < 2; r++) {
                    res.ans[l][r] = max(a.ans[l][1] + b.ans[0][r], a.ans[l][0] + b.ans[1][r]);
                }
            }
        }

        return res;
    }

    int val(int v) {
        if (v < 0) {
            return -1;
        }
        if (v > 0) {
            return 1;
        }

        return 0;
    }

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, Node());
    }

    void build(vector<ll>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size()) {
                tree[x].ans[1][1] = abs(a[lx]);
                tree[x].sign[0] = tree[x].sign[1] = val(a[lx]);
            }

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(vector<ll>& a) {
        return build(a, 0, 0, size);
    }

    void set(int i, ll v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x].ans[1][1] = abs(v);
            tree[x].sign[0] = tree[x].sign[1] = val(v);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            set(i, v, 2 * x + 1, lx, mid);
        }
        else {
            set(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, ll v) {
        set(i, v, 0, 0, size);
    }

    ll calc(int l, int r) {
        return tree[0].ans[1][1];
    }
};

int N, Q;
SegTree st;
vector<int> A;
vector<ll> D;

int main(void)
{
    scanf("%d %d", &N, &Q);

    A.resize(N);
    st.init(N - 1);
    D.resize(N - 1);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        D[i] = A[i + 1] - A[i];
    }
    st.build(D);

    while (Q--) {
        int l, r, x;
        scanf("%d %d %d", &l, &r, &x);
        l--; l--;
        r--;

        if (l >= 0) {
            D[l] += x;
            st.set(l, D[l]);
        }
        if (r < N - 1) {
            D[r] -= x;
            st.set(r, D[r]);
        }

        printf("%lld\n", st.calc(0, N - 1));
    }

    return 0;
}