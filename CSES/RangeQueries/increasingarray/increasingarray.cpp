#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int INF = 1e9 + 1;

struct SegTree {

    int size;
    vector<ll> tree;

    void init(int n) {
        size =1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, 0);
    }

    void set(int i, ll v, int x, int lx, int rx) {
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
    void set(int i, ll v) {
        assert(v >= 0);
        set(i, v, 0, 0, size);
    }

    ll sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        return sum(l, r, 2 * x + 1, lx, mid) + sum(l, r, 2 * x + 2, mid, rx);
    }
    ll sum(int l, int r) {
        ll ret = sum(l, r, 0, 0, size);
        assert(ret >= 0);

        return ret;
    }
};

int n, q;
vector<ll> pref;
vector<int> x;
SegTree operations;
vector<int> mj;
vector<ll> ans;

vector<pair<pi, int>> queries;

bool gcomp(const int& a, const int& b)
{
    return a > b;
}

int main(void)
{
    scanf("%d %d", &n, &q);

    pref.resize(n + 1);
    x.resize(n + 1);
    ans.resize(q);
    queries.resize(q);
    operations.init(n + 1);

    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);
    x[n] = INF;
    pref[0] = x[0];
    for (int i = 1; i < n; i++)
        pref[i] = pref[i - 1] + x[i];

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &queries[i].first.first, &queries[i].first.second);
        queries[i].first.first--;
        queries[i].first.second--;
        queries[i].second = i;
    }
    sort(queries.rbegin(), queries.rend());

    mj.push_back(n);

    int qpointer = 0;
    for (int ind = n - 1; ind >= 0; ind--) {
        while (x[mj.back()] <= x[ind]) {
            operations.set(mj.back(), 0);
            mj.pop_back();
        }

        int len = mj.back() - ind - 1;
        operations.set(ind, (ll) len * x[ind] - (pref[mj.back() - 1] - pref[ind]));
        mj.push_back(ind);

        while (qpointer < q && queries[qpointer].first.first == ind) {

            ll res = 0;
            int last = lower_bound(mj.begin(), mj.end(), queries[qpointer].first.second, gcomp) - mj.begin();
            last = mj[last];

            res = operations.sum(ind, last);
            int len = queries[qpointer].first.second - last;
            if (len != -1)
                res += ((ll)len * x[last]) - (pref[queries[qpointer].first.second] - pref[last]);

            ans[queries[qpointer].second] = res;
            qpointer++;
        }
    }

    for (int i = 0; i < q; i++)
        printf("%lld\n", ans[i]);

    return 0;
}