#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;

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
        if (lx >= r || l >= rx) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        return calc(l, r , 2 * x + 1, lx, mid) + calc(l, r, 2 * x + 2, mid, rx);
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int n;
SegTree taller_cows;
vector<pi> h;
int ans = 0;

int main(void)
{
    freopen("bphoto.in", "r", stdin);
    freopen("bphoto.out", "w", stdout);

    scanf("%d", &n);
    h.resize(n);
    taller_cows.init(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &h[i].f);
        h[i].s = i;
    }
    sort(h.rbegin(), h.rend());

    int curh = INT_MAX;
    vector<int> waiting;

    for (int i = 0; i < n; i++) {
        if (h[i].f < curh) {
            for (auto c : waiting)
                taller_cows.set(c, 1);
            waiting.clear();

            curh = h[i].f;
        }

        int l = taller_cows.calc(0, h[i].s);
        int r = taller_cows.calc(h[i].s + 1, n);

        ans += min(l, r) * 2 < max(l, r);

        waiting.push_back(h[i].s);
    }

    printf("%d\n", ans);
    return 0;
}