#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {

    int size;
    vector<ll> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, 0);
    }

    void add(int i, ll v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            add(i, v, 2 * x + 1, lx, mid);
        else
            add(i, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
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

        return calc(l, r, 2 * x + 1, lx, mid) + calc(l, r, 2 * x + 2, mid, rx);
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int n;
vector<int> a;

SegTree numbers;
SegTree inversions;
ll ans = 0;

int main(void)
{
    scanf("%d", &n);
    a.resize(n);

    numbers.init(n + 1);
    inversions.init(n + 1);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < n; i++) {
        ll simple_inv = numbers.calc(a[i] + 1, n + 1);
        ans += inversions.calc(a[i] + 1, n + 1);

        inversions.add(a[i], simple_inv);
        numbers.add(a[i], 1);
    }

    printf("%lld\n", ans);
}