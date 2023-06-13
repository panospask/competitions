#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

struct SegTree {
    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, 0);
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

    int calc(int l, int r, int x, int lx, int rx) {
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
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int n;
vector<int> prv;
vector<int> a;
ll ans = 0;
SegTree open_segments;

int main(void)
{
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);

    scanf("%d", &n);

    open_segments.init(2 * n);
    prv.assign(n + 1, -1);
    a.resize(2 * n);

    for (int i = 0; i < 2 * n; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < 2 * n; i++) {
        if (prv[a[i]] == -1) {
            prv[a[i]] = i;
            open_segments.set(i, 1);
        }
        else {
            ans += open_segments.calc(prv[a[i]] + 1, i);
            open_segments.set(prv[a[i]], 0);
        }
    }

    printf("%lld\n", ans);

    return 0;
}