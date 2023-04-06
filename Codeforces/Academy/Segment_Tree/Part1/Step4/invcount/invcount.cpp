#include <bits/stdc++.h>
#define MAXA 40
#define MAXN 100000

using namespace std;

int n, m;

struct node {   
    int freq[MAXA]; //freq[i]: How many numbers less than or equal to i 
    long long int inv;

    node(void) {
        memset(freq, 0, sizeof(freq));
        inv = 0;
    }
};
typedef struct node Node;

Node single(int a) 
{
    Node s;

    for (int i = a; i < MAXA; i++)
        s.freq[i] = 1;
    s.inv = 0;

    return s;
}

Node IDENTITY;

Node merge(Node& a, Node& b) 
{
    Node c;

    // Merge inversions
    c.inv = a.inv + b.inv;
    for (int i = 1; i < MAXA; i++) {
        int b_lower = b.freq[i-1]; // How many numbers are less than i in b
        int a_equal = a.freq[i] - a.freq[i-1]; // How many numbers are equal to i in a

        c.inv += (long long int) b_lower * a_equal;
    }

    // Merge frequencies
    for (int i = 0; i < MAXA; i++) {
        c.freq[i] = a.freq[i] + b.freq[i];
    }

    return c;
}

struct segtree {

    int size;
    vector<Node> tree;

    void init(int n)
    {
        size = 1;
        while (size < n) {
            size *= 2;
        }

        tree.resize(size * 2);
    }

    void build(int* a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < n) 
                tree[x] = single(a[lx]);
            else 
                tree[x] = IDENTITY;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(int* a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = single(v);
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

    Node calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            // Disjoint segments
            return IDENTITY;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        auto s1 = calc(l, r, 2 * x + 1, lx, mid);
        auto s2 = calc(l, r, 2 * x + 2, mid, rx);

        return merge(s1, s2);
    }
    Node calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

segtree st;
int a[MAXN + 2];

int main(void)
{
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i]--;
    }

    st.init(n);
    st.build(a);

    while (m--) {
        int op;
        scanf("%d", &op);
        if (op == 2) {
            int i, v;
            scanf("%d %d", &i, &v);
            i--; v--;

            st.set(i, v);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;

            long long ans = st.calc(l, r).inv;
            printf("%lld\n", ans);
        }
    }
    return 0;
}