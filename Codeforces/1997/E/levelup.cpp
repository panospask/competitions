#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int MAXA = 2e5;

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

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;

        return calc(l, r, 2 * x + 1, lx, mid) + calc(l, r, 2 * x + 2, mid, rx);
    }

    // Returns the kth one
    int kth_one(int& k, int x, int lx, int rx) {
        if (tree[x] < k) {
            k -= tree[x];
            return -1;
        }
        if (lx == rx - 1) {
            return lx;
        }

        int mid = (lx + rx) / 2;
        int ans = kth_one(k, 2 * x + 1, lx, mid);
        if (ans == -1) {
            ans = kth_one(k, 2 * x + 2, mid, rx);
        }

        return ans;
    }

    // Return the position of the kth one after i (including i)
    // Return -1 if kth one after i does not exist
    int kth_after(int i, int k) {
        int tot = k + calc(0, i, 0, 0, size);
        return kth_one(tot, 0, 0, size);
    }
};

int N, Q;
vector<int> a;
vector<vector<int>> values;

// change[k][i]: The position at which the level of hero moves up to i + 1 when K = k
vector<vector<int>> change;

SegTree st;

int main(void)
{
    scanf("%d %d", &N, &Q);

    a.resize(N);
    change.resize(N + 1);
    values.resize(MAXA + 1);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        values[a[i]].pb(i);
    }
    for (int i = 0; i <= N; i++) {
        change[i].pb(0);
    }

    st.init(N);
    for (int i = 0; i < N; i++) {
        st.add(i, 1);
    }

    // Latest k s.t the hero is able to level up
    int latest = N;
    for (int level = 1; level <= N; level++) {

        for (int k = latest; k > 0; k--) {
            int res = st.kth_after(change[k][level - 1], k);
            if (res == -1) {
                latest = k - 1;
            }
            else {
                change[k].pb(res + 1);
            }
        }        

        // Remove the values of current level
        for (auto v : values[level]) {
            st.add(v, -1);
        }
    }

    while (Q--) {
        int i, k;
        scanf("%d %d", &i, &k);
        i--;

        if (change[k].size() <= a[i] || change[k][a[i]] > i) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }

    return 0;
}