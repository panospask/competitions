#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

struct SegTree {
    int size;
    vector<int> tree;
    int tot;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, 0);
        tot = 0;
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            tot += v;
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
    int get(int fence) {
        int c1 = sum(0, fence);
        int c2 = tot - c1;

        return max(c1, c2);
    }

    // This function searches on both segtrees simultaneously, reducing the query time from O(log^2(N)) to O(logN)
    int answer(SegTree& other) {
        int up = 0, other_up = 0;
        int down = 0, other_down = 0;

        int x = 0;
        while (2 * x + 2 < tree.size()) {
            int l = 2 * x + 1;
            int r = 2 * x + 2;

            if (max(down + tree[l], other_down + other.tree[l]) < max(up + tree[r], other_up + other.tree[r])) {
                down += tree[l];
                other_down += other.tree[l];
                x = r;
            }
            else {
                up += tree[r];
                other_up += other.tree[r];
                x = l;
            }
        }

        // Only one coordinate left to add, decide which side gets it
        if (max(down + tree[x], other_down + other.tree[x]) < max(up + tree[x], other_up + other.tree[x])) {
            down += tree[x];
            other_down += other.tree[x];
        }
        else {
            up += tree[x];
            other_up += other.tree[x];
        }

        int m1 = max(up, down);
        int m2 = max(other_down, other_up);

        return max(m1, m2);
    }
};

int N;
vector<pi> cows;
SegTree st[2];

vector<int> x, y;

void codify(vector<int>& v)
{
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
}

int code(int x, vector<int>& v)
{
    return lower_bound(v.begin(), v.end(), x) - v.begin();
}

int get(int fence)
{
    return max(st[0].get(fence), st[1].get(fence));
}

// Using calculate results in O(log^2(N)) time complexity
int calculate(void)
{
    int l = 0;
    int r = y.size();

    while (l + 1 < r) {
        int m1 = (l + l + r) / 3;
        int m2 = (l + r + r) / 3;

        int r1 = get(m1);
        int r2 = get(m2);

        if (r1 < r2) {
            r = m2 - 1;
        }
        else if (r1 > r2) {
            l = m1 + 1;
        }
        else {
            r = m2;
            l = m1;
        }
    }

    return min(get(l), get(r));
}

int main(void)
{
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);

    scanf("%d", &N);

    cows.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &cows[i].first, &cows[i].second);

        x.pb(cows[i].first);
        y.pb(cows[i].second);
    }
    
    codify(x);
    codify(y);
    st[0].init(y.size());
    st[1].init(y.size());

    sort(cows.begin(),cows.end());
    for (int i = 0; i < N; i++) {
        cows[i].first = code(cows[i].first, x);
        cows[i].second = code(cows[i].second, y);

        st[1].add(cows[i].second, 1);
    }

    int p = 0;
    int ans = N;
    for (int i = 0; i < x.size(); i++) {
        while (p < N && cows[p].first <= i) {
            st[1].add(cows[p].second, -1);
            st[0].add(cows[p].second, 1);
            p++;
        }

        ans = min(ans, st[0].answer(st[1]));
    }

    printf("%d\n", ans);

    return 0;
}