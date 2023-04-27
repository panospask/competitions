#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

struct item {
    ll no_max;
    ll l_max;
    ll r_max;
    ll bothmax;
};
typedef struct item Item;

const Item IDENTITY = {0, 0, 0, 0};

Item merge(Item& a, Item& b)
{
    Item c;
    c.no_max = max(a.r_max + b.no_max, a.no_max + b.l_max);
    c.l_max = max(a.bothmax + b.no_max, a.l_max + b.l_max);
    c.r_max = max(a.no_max + b.bothmax, a.r_max + b.r_max);
    c.bothmax = max(a.bothmax + b.r_max, a.l_max + b.bothmax);

    return c;
}

Item single(int a)
{
    Item c;
    c.bothmax = a;
    c.l_max = c.r_max = c.no_max = 0;
    return c;
}

struct segtree {

    int size;
    ll max_element;
    vector<Item> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
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
    void build(vector<int>& a) {
        build(a, 0, 0, size);
        max_element = tree[0].bothmax;
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
        max_element = tree[0].bothmax;
    }
};

int n, d;
segtree st;
vector<int> m;

int main(void)
{
    freopen("optmilk.in", "r", stdin);
    freopen("optmilk.out", "w", stdout);

    scanf("%d %d", &n, &d);
    st.init(n);
    m.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &m[i]);
    st.build(m);

    long long ans = 0;
    while (d--) {
        int i, v;
        scanf("%d %d", &i, &v);
        i--;
        st.set(i, v);
        ans += st.max_element;
    }

    printf("%lld\n", ans);
    return 0;
}