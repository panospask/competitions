#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    int size;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size = size * 2;
        }

        tree.assign(2 * size, 0);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            set(i, v, 2 * x + 1, lx, mid);
        }
        else {
            set(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        int c1 = calc(l, r, 2 * x + 1, lx, mid);
        int c2 = calc(l, r, 2 * x + 2, mid, rx);
        return max(c1, c2);
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N, M, K;
vector<int> a, b;

// s1[v]: Max length of a sequence that **decreases in the last step** and the last value is v
// s2[v]: Same for sequence that increases in the last step 
SegTree s1, s2;

vector<int> x;

int find(int v) {
    return lower_bound(x.begin(), x.end(), v) - x.begin();
}

int main(void) {
    cin >> N;

    a.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        x.push_back(a[i]);
    }
    cin >> M;
    b.resize(M + 1);
    for (int i = 1; i <= M; i++) {
        cin >> b[i];
        x.push_back(b[i]);
    }
    sort(x.begin(), x.end());
    x.resize(unique(x.begin(), x.end()) - x.begin());

    K = x.size();
    s1.init(K);
    s2.init(K);

    int ans = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (a[i] != b[j]) {
                continue;
            }

            int cur = find(a[i]);
            // Make this an increasing step
            int res1 = s1.calc(0, cur) + 1;
            // Now make this a decreasing step
            int res2 = s2.calc(cur + 1, K) + 1;
            
            ans = max(ans, max(res1, res2));
            s2.set(cur, res1);
            s1.set(cur, res2);
        }
    }

    cout << ans << endl;
}