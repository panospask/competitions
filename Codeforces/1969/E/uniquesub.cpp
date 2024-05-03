#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    int size;
    vector<int> tree;
    vector<int> op;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, 0);
        op.assign(2 * size, 0);
    }

    void propagate(int x) {
        tree[2 * x + 1] += op[x];
        tree[2 * x + 2] += op[x];
        op[2 * x + 1] += op[x];
        op[2 * x + 2] += op[x];

        op[x] = 0;
    }

    void add(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x] += v;
            op[x] += v;
            return;
        }

        propagate(x);
        int mid = (lx + rx) / 2;

        add(l, r, v, 2 * x + 1, lx, mid);
        add(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int l, int r, int v) {
        return add(l, r, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 1e9 + 5;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x);
        int mid = (lx + rx) / 2;

        int c1 = calc(l, r, 2 * x + 1, lx, mid);
        int c2 = calc(l, r, 2 * x + 2, mid, rx);

        return min(c1, c2);
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N;
vector<int> a;
SegTree st;
unordered_map<int, int> occ, soc;

void solve(void)
{
    scanf("%d", &N);

    occ.clear();
    soc.clear();
    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    st.init(N);
    int l = 0;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (occ.count(a[i]) == 0) {
            occ[a[i]] = l - 1;
        }
        if (soc.count(a[i]) == 0) {
            soc[a[i]] = l - 1;
        }
        st.add(soc[a[i]] + 1, occ[a[i]] + 1, -1);
        st.add(occ[a[i]] + 1, i + 1, 1);
        soc[a[i]] = occ[a[i]];
        occ[a[i]] = i;

        if (st.calc(l, i + 1) == 0) {
            ans++;
            l = i + 1;
            occ.clear();
            soc.clear();
        }

    }

    printf("%d\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}