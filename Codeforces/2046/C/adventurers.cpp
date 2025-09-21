#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e9;

struct SegTree {
    int size;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, 0);
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            add(i, v, 2 * x + 1, lx, mid);
        }
        else {
            add(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    int sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        return sum(l, r, 2 * x + 1, lx, mid) + sum(l, r, 2 * x + 2, mid, rx);
    }
    int sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }

    int lb(int s, int x, int lx, int rx) {
        if (tree[x] < s) {
            return -1;
        }
        if (lx == rx - 1) {
            return lx;
        }

        int mid = (lx + rx) / 2;

        int res = lb(s, 2 * x + 1, lx, mid);
        if (res == -1) {
            res = lb(s - tree[2 * x + 1], 2 * x + 2, mid, rx);
        }

        return res;
    }
    int lb(int s) {
        return lb(s, 0, 0, size);
    }
};

int N;
vector<pi> cities;

// Compression of coordinates
vector<int> xcord;
vector<int> ycord;

// Cities by x-cord (compressed)
vector<vector<int>> by_x;

SegTree l, r;

void compress(vector<int>& v) {
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
}

int find(int a, vector<int>& v) {
    return lower_bound(v.begin(), v.end(), a) - v.begin();
}

int doable(int x) {
    int s1 = l.lb(x);
    int s2 = r.lb(x);

    int s = max(s1, s2);
    if (l.sum(s + 1, ycord.size()) >= x && r.sum(s + 1, ycord.size()) >= x) {
        return s;
    }
    else {
        return -1;
    }
}

void solve(void) {
    xcord.clear();
    ycord.clear();
    by_x.clear();

    scanf("%d", &N);

    cities.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &cities[i].first, &cities[i].second);
        xcord.pb(cities[i].first);
        ycord.pb(cities[i].second);
    }

    compress(xcord);
    compress(ycord);

    by_x.resize(xcord.size());
    l.init(ycord.size());
    r.init(ycord.size());

    for (int i = 0; i < N; i++) {
        cities[i].first = find(cities[i].first, xcord);
        cities[i].second = find(cities[i].second, ycord);

        by_x[cities[i].first].pb(cities[i].second);
        r.add(cities[i].second, 1);
    }

    int ans = 0;
    pi square = {INF - 1, INF - 1};
    for (int idx = 0; idx < xcord.size(); idx++) {
        // Move some things
        for (auto y : by_x[idx]) {
            l.add(y, 1);
            r.add(y, -1);
        }

        int a = 0;
        int b = N / 4 + 1;
        while (a + 1 < b) {
            int mid = (a + b) / 2;
            if (doable(mid) != -1) {
                a = mid;
            }
            else {
                b = mid;
            }
        }

        if (a > ans) {
            ans = a;
            square = {xcord[idx], ycord[doable(a)]};
        }
    }

    printf("%d\n", ans);
    printf("%d %d\n", square.first + 1, square.second + 1);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}