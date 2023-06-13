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

    void add(int i, int v, int x, int lx, int rx) {
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
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    int sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        int s1 = sum(l, r, 2 * x + 1, lx, mid);
        int s2 = sum(l, r, 2 * x + 2, mid, rx);

        return s1 + s2;
    }
    int sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};

int n;
vector<int> bottompos;
vector<int> toppos;
SegTree vals;

ll inversions = 0;
ll ans = 0;
vector<int> res;

ll solve(void)
{
    // Must find the cyclic shift of res that minimizes inversions

    vals.init(n);
    inversions = 0;
    // Count initial inversions
    for (int i = 0; i < n; i++) {
        inversions += vals.sum(res[i] + 1, n);
        vals.add(res[i], 1);
    }

    ll init_inv = inversions;
    ll ans = inversions;

    for (int i = n - 1; i >= 0; i--) {
        // Move i to the front

        // Everything that is not bigger is less
        // and it will become an inversion
        ll rminv = n - 1 - res[i];
        int addinv = res[i];

        inversions += addinv - rminv;

        ans = min(ans, inversions);
    }

    assert(inversions == init_inv);

    return ans;
}

int main(void)
{
    freopen("mincross.in", "r", stdin);
    freopen("mincross.out", "w", stdout);

    scanf("%d", &n);

    bottompos.resize(n);
    toppos.resize(n);
    res.resize(n);
    vals.init(n);

    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        num--;

        bottompos[num] = i;
    }
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        num--;

        toppos[num] = i;
    }

    for (int i = 0; i < n; i++) {
        res[toppos[i]] = bottompos[i];
    }
    ans = solve();

    for (int i = 0; i < n; i++)
        res[bottompos[i]] = toppos[i];

    ans = min(ans, solve());

    printf("%lld\n", ans);

    return 0;
}