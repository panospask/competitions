#include "wall.h"
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e6;

struct SegTree {
    int size;
    vector<pi> tree;
    const pi DEFAULT = {0, INF};

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, DEFAULT);
    }

    void minimize(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r || tree[x].first >= v) {
            return;
        }
        v = min(v, tree[x].second);
        if (l <= lx && rx <= r) {
            tree[x].first = v;
            return;
        }

        int mid = (lx + rx) / 2;
        minimize(l, r, v, 2 * x + 1, lx, mid);
        minimize(l, r, v, 2 * x + 2, mid, rx);
    }
    void minimize(int l, int r, int v) {
        minimize(l, r, v, 0, 0, size);
    }

    void maximize(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r || tree[x].second <= v) {
            return;
        }
        v = max(v, tree[x].first);
        if (l <= lx && rx <= r) {
            tree[x].second = v;
            return;
        }

        int mid = (lx + rx) / 2;
        maximize(l, r, v, 2 * x + 1, lx, mid);
        maximize(l, r, v, 2 * x + 2, mid, rx);
    }
    void maximize(int l, int r, int v) {
        maximize(l, r, v, 0, 0, size);
    }

    void result(vector<int>& a, pi res, int x, int lx, int rx) {
        res.first = min(res.first, tree[x].second);
        res.first = max(tree[x].first, res.first);

        res.second = max(res.second, tree[x].first);
        res.second = min(tree[x].second, res.second);
        if (lx == rx - 1) {
            if (lx < a.size()) {
                a[lx] = res.first;
            }
            return;
        }

        int mid = (lx + rx) / 2;
        result(a, res, 2 * x + 1, lx, mid);
        result(a, res, 2 * x + 2, mid, rx);
    }
    void result(vector<int>& a) {
        result(a, DEFAULT, 0, 0, size);
    }
};

SegTree st;

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[])
{
    st.init(n);

    for (int i = k - 1; i >= 0; i--) {
        if (op[i] == 1) {
            st.minimize(left[i], right[i] + 1, height[i]);
        }
        else {
            st.maximize(left[i], right[i] + 1, height[i]);
        }
    }

    vector<int> ans(n);
    st.result(ans);

    for (int i = 0; i < n; i++) {
        finalHeight[i] = ans[i];
    }
}