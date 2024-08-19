#include <bits/stdc++.h>
#include "holiday.h"

using namespace std;

typedef long long ll;

const ll INF = 2e18;

struct SegTree {
    struct Node {
        ll sum = 0;
        int cnt = 0;
    };

    Node merge(Node a, Node b) {
        return {a.sum + b.sum, a.cnt + b.cnt};
    }

    int size;
    vector<Node> tree;

    void init(int N) {
        size = 1;

        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, {0, 0});
    }

    void add(int i, Node v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = merge(tree[x], v);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            add(i, v, 2 * x + 1, lx, mid);
        }
        else {
            add(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int i, int x, int c) {
        add(i, {x, c}, 0, 0, size);
    }

    ll getsum(int k, int x, int lx, int rx) {
        if (k >= tree[x].cnt) {
            return tree[x].sum;
        }
        else if (tree[x].cnt == 0) {
            return 0;
        }
        else if (lx == rx - 1) {
            // Take **some** of these values
            ll v = tree[x].sum / tree[x].cnt;

            return v * k; 
        }

        ll res = 0;
        int mid = (lx + rx) / 2;
        res = getsum(k, 2 * x + 1, lx, mid);
        if (tree[2 * x + 1].cnt < k) {
            res += getsum(k - tree[2 * x + 1].cnt, 2 * x + 2, mid, rx);
        }

        return res;
    }
    ll getsum(int k) {
        return getsum(k, 0, 0, size);
    }
};

int N, D;
SegTree st;
vector<int> values;
vector<int> a;

int pos(int v)
{
    return values.size() - 1 - (lower_bound(values.begin(), values.end(), v) - values.begin());
}

void calculate(int s, int l, int r, int optl, int optr, int mod, vector<ll>& ans)
{
    if (optl >= N) {
        return;
    }

    int mid = (l + r) / 2;
    ll maxv = 0;
    int maxp = optl;
    
    for (int i = optl; i <= optr; i++) {
        st.add(pos(a[i]), a[i], 1);

        int rem = max(mid - (i - s) * mod, 0);
        ll cur = st.getsum(rem);

        if (cur > maxv) {
            maxv = cur;
            maxp = i;
        }
    }

    ans[mid] = maxv;

    for (int i = optl; i <= optr; i++) {
        st.add(pos(a[i]), -a[i], -1);
    }

    if (mid == l) {
        return;
    }

    calculate(s, l, mid, optl, maxp, mod, ans);

    for (int i = optl; i < maxp; i++) {
        st.add(pos(a[i]), a[i], 1);
    }
    calculate(s, mid, r, maxp, optr, mod, ans);
    for (int i = optl; i < maxp; i++) {
        st.add(pos(a[i]), -a[i], -1);
    }
}

long long int findMaxAttraction(int n, int start, int d, int attraction[])
{
    // Hope this works
    N = n;
    D = d;

    values.resize(N);
    a.resize(N);

    for (int i = 0; i < N; i++) {
        values[i] = attraction[i];
        a[i] = attraction[i];
    }
    sort(values.begin(), values.end());
    values.resize(unique(values.begin(), values.end()) - values.begin());

    st.init(values.size());

    vector<ll> aft1(D + 1), aft2(D + 1);
    calculate(start, 0, D + 1, start + 1, N - 1, 1, aft1);
    calculate(start, 0, D + 1, start + 1, N - 1, 2, aft2);

    reverse(a.begin(), a.end());
    start = N - start - 1;
    vector<ll> bef1(D + 1), bef2(D + 1);
    calculate(start, 0, D + 1, start + 1, N - 1, 1, bef1);
    calculate(start, 0, D + 1, start + 1, N - 1, 2, bef2);

    ll ans = 0;
    for (int p1 = 0; p1 <= D; p1++) {
        int p2 = D - p1;

        ans = max(ans, aft1[p1] + bef2[p2]);
        ans = max(ans, bef1[p1] + aft2[p2]);

        if (p1) {
            ans = max(ans, aft1[p1 - 1] + a[start] + bef2[p2]);
            ans = max(ans, bef1[p1 - 1] + a[start] + aft2[p2]);
        }
        if (p2) {
            ans = max(ans, aft1[p1] + a[start] + bef2[p2 - 1]);
            ans = max(ans, bef1[p1] + a[start] + aft2[p2 - 1]);
        }
    }

    return ans;
}