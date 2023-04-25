#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

struct segtree {

    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = a[lx];
            else
                tree[x] = 0;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int get(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        auto s1 = get(l, r, 2 * x + 1, lx, mid);
        auto s2 = get(l, r, 2 * x + 2, mid, rx);

        return s1 + s2;
    }
    int get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

int n;
vector<int> a;
vector<int> valcount;

// inv_of_val[i] is the number of inversions with i as the smallest number
vector<long int> inv_of_val;

// pref_sum[i] is the number of inversions when all numbers are cut down to i
vector<long long int> pref_sum;
segtree st;

int main(void)
{
    freopen("haircut.in", "r", stdin);
    freopen("haircut.out", "w", stdout);

    scanf("%d", &n);
    st.init(n + 1);
    a.resize(n);
    valcount.resize(n + 1);
    inv_of_val.resize(n + 1);
    pref_sum.resize(n + 1);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < n; i++) {
        int val = a[i];
        inv_of_val[val] += st.get(val + 1, n + 1);

        st.set(val, ++valcount[val]);
    }

    pref_sum[0] = 0;
    for (int i = 1; i < n; i++) {
        pref_sum[i] = pref_sum[i-1] + inv_of_val[i-1];
    }

    for (int i = 0; i < n; i++) {
        printf("%lld\n", pref_sum[i]);
    }

    return 0;
}