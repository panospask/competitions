#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

struct SegTree {
    const int NEUTRAL = 0;
    const int NO_OP = 0;

    int size;
    vector<int> op;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, NEUTRAL);
        op.assign(2 * size, NO_OP);
    }

    void propagate(int x) {
        tree[2 * x + 1] += op[x];
        tree[2 * x + 2] += op[x];
        op[2 * x + 1] += op[x];
        op[2 * x + 2] += op[x];

        op[x] = NO_OP;
    }

    void modify(int l, int r, int v, int x, int lx, int rx) {
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
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void modify(int l, int r, int v) {
        modify(l, r, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        int c1 = calc(l, r, 2 * x + 1, lx, mid);
        int c2 = calc(l, r, 2 * x + 2, mid, rx);

        return max(c1, c2);
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};
struct Query {
    int i1, i2, val;
};
struct Rect {
    int x1, y1, x2, y2;
    int g;
};

int n, k;
vector<int> x_cords;
vector<int> y_cords;
vector<Rect> rects;
vector<vector<Query>> queries;
SegTree st;

int find(int x, vector<int>& v)
{
    return lower_bound(v.begin(), v.end(), x) - v.begin();
}

int main(void)
{
    freopen("lazy.in", "r", stdin);
    freopen("lazy.out", "w", stdout);


    scanf("%d %d", &n, &k);
    rects.resize(n);
    for (int i = 0; i < n; i++) {
        int g, x, y;
        scanf("%d %d %d", &g, &x, &y);

        int x1 = x - k - y;
        int y1 = x - k + y;
        int x2 = x + k - y;
        int y2 = x + k + y;
        x_cords.push_back(x1);
        x_cords.push_back(x2);
        y_cords.push_back(y1);
        y_cords.push_back(y2);

        rects[i] = {x1, y1, x2, y2, g};
    }

    sort(x_cords.begin(), x_cords.end());
    x_cords.resize(unique(x_cords.begin(), x_cords.end()) - x_cords.begin());
    sort(y_cords.begin(), y_cords.end());
    y_cords.resize(unique(y_cords.begin(), y_cords.end()) - y_cords.begin());

    queries.resize(x_cords.size() + 1);
    for (int i = 0; i < n; i++) {
        int x1 = find(rects[i].x1, x_cords);
        int x2 = find(rects[i].x2, x_cords);
        int y1 = find(rects[i].y1, y_cords);
        int y2 = find(rects[i].y2, y_cords);

        queries[x1].push_back({y1, y2, rects[i].g});
        queries[x2 + 1].push_back({y1, y2, -rects[i].g});
    }

    st.init(y_cords.size());
    int ans = 0;

    for (int x = 0; x < x_cords.size(); x++) {
        // Process the queries in x;
        for (auto q : queries[x])
            st.modify(q.i1, q.i2 + 1, q.val);

        ans = max(ans, st.calc(0, y_cords.size()));
    }

    printf("%d\n", ans);

    return 0;
}