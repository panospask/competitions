#include "candies.h"
#define mp make_pair
#define pb push_back
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef pair<int, int> pi;

// RSPQ
struct SegTree {
    int size;
    vector<int> tree;

    void init(int n, int v) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, v);
    }

    void set(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        set(l, r, v, 2 * x + 1, lx, mid);
        set(l, r, v, 2 * x + 2, mid, rx);

        return;
    }
    void set(int l, int r, int v) {
        set(l, r, v, 0, 0, size);
    }

    int get(int i, int x, int lx, int rx) {
        if (lx == rx - 1) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        int res = 0;
        if (i < mid)
            res = get(i, 2 * x + 1, lx, mid);
        else
            res = get(i, 2 * x + 2, mid, rx);

        return max(res, tree[x]);
    }
    int get(int i) {
        return get(i, 0, 0, size);
    }
};

int N, Q;
vector<int> C, L, R, V;

vector<int> brute_force(void)
{
    vector<int> cnt(N, 0);

    for (int i = 0; i < Q; i++) {
        for (int p = L[i]; p <= R[i]; p++)
            cnt[p] = min(C[p], max(cnt[p] + V[i], 0));
    }

    return cnt;
}

vector<int> sub2(void)
{
    vector<ll> p_inv(N + 1);
    for (int i = 0; i < Q; i++) {
        p_inv[L[i]] += V[i];
        p_inv[R[i] + 1] -= V[i];
    }

    for (int i = 1; i < N; i++)
        p_inv[i] += p_inv[i - 1];

    p_inv.pop_back();
    for (int i = 0; i < N; i++)
        p_inv[i] = min(p_inv[i], (ll)C[i]);

    vector<int> ans;
    for (auto v : p_inv)
        ans.push_back(v);

    return ans;
}

SegTree setmin, setmax;
vector<ll> prefqueries;
vector<pi> vals;

ll getval(int i)
{
    int s1 = setmin.get(i);
    int s2 = setmax.get(i);

    int initial;
    int t;
    if (s1 > s2) {
        initial = 0;
        t = s1;
    }
    else {
        initial = vals[i].first;
        t = s2;
    }

    return prefqueries.back() - prefqueries[t] + initial;
}

vector<int> distribute_candies(vector<int> c, vector<int> l, vector<int> r, vector<int> v)
{
    N = c.size();
    Q = l.size();
    C = c;
    R = r;
    L = l;
    V = v;

    // if (N <= 2000 && Q <= 2000) {
        // return brute_force();
    // }

    bool is2 = true;
    for (int i = 0; i < Q; i++) {
        is2 = is2 && V[i] >= 0;
    }

    if (is2)
        return sub2();


    // Go subtask 4
    vals.resize(N);
    for (int i = 0; i < N; i++)
        vals[i] = mp(C[i], i);

    sort(vals.begin(), vals.end());

    setmin.init(N, 0);
    setmax.init(N, -1);

    prefqueries.pb(0);
    for (int q = 0; q < Q; q++) {
        prefqueries.pb(prefqueries.back() + V[q]);

        int l = -1;
        int r = N;
        while (r > l + 1) {
            int mid = (l + r) / 2;
            ll v = getval(mid);
            if (v < 0 || v > vals[mid].first) {
                l = mid;
            }
            else {
                r = mid;
            }
        }

        if (V[q] > 0) {
            setmax.set(0, l + 1, q + 1);
        }
        else if (V[q] < 0) {
            setmin.set(0, l + 1, q + 1);
        }
    }

    vector<int> ans(N);
    for (int i = 0; i < N; i++)
        ans[vals[i].second] = getval(i);

    return ans;
}