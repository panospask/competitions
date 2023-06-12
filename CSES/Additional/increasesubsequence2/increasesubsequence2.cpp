#include <bits/stdc++.h>
#define MOD ((int)1e9 + 7)

using namespace std;

typedef long long ll;

struct SegTree {

    int size;
    vector<ll> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, 0ll);
    }

    void add(int i, ll v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            tree[x] %= MOD;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            add(i, v, 2 * x + 1, lx, mid);
        else
            add(i, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
        tree[x] %= MOD;
    }
    void add(int i, ll v) {
        add(i, v, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ll s1 = calc(l, r, 2 * x + 1, lx, mid);
        ll s2 = calc(l, r, 2 * x + 2, mid, rx);

        return (s1 + s2) % MOD;
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int n;
vector<int> a;
set<int> vals;
vector<int> pos;

int main(void)
{
    scanf("%d", &n);
    a.resize(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);

        if (vals.find(a[i]) == vals.end()) {
            pos.push_back(a[i]);
            vals.insert(a[i]);
        }
    }

    sort(pos.begin(), pos.end());

    SegTree total_number;
    total_number.init(vals.size());

    for (int i = 0; i < n; i++) {
        int curpos = lower_bound(pos.begin(), pos.end(), a[i]) - pos.begin();
        ll curttl = 1 + total_number.calc(0, curpos);

        total_number.add(curpos, curttl);
    }

    printf("%lld\n", total_number.calc(0, vals.size()));

    return 0;
}