#include <bits/stdc++.h>

using namespace std;

struct segtree {
    
    int size = 0;
    vector<int> values;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        values.resize(size * 2);
    }

    void build(vector<int>& a, int x, int l_x, int r_x) {
        if (l_x == r_x - 1) {
            if (l_x < (int)a.size())
                values[x] = a[l_x];
            else 
                values[x] = 0;
            
            return;
        }

        int mid = (l_x + r_x) / 2;
        build(a, 2 * x + 1, l_x, mid);
        build(a, 2 * x + 2, mid, r_x);

        values[x] = max(values[2 * x+ 1], values[2 * x + 2]);
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int l_x, int r_x) {
        if (l_x == r_x - 1) {
            values[x] = v;
            return;
        }

        int mid = (l_x + r_x) / 2;
        if (i < mid) 
            set(i, v, 2 * x + 1, l_x, mid);
        else 
            set(i, v, 2 * x + 2, mid, r_x);

        values[x] = max(values[2 * x+ 1], values[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int query(int l, int r, int x, int l_x, int r_x) {
        if (l <= l_x && r_x <= r) {
            // Fully contained
            return values[x];
        }
        else if (l >= r_x || l_x >= r) {
            // Disjoint segments
            return 0;
        }

        int mid = (l_x + r_x) / 2;
        int m1 = query(l, r, 2 * x + 1, l_x, mid);
        int m2 = query(l, r, 2 * x + 2, mid, r_x);
        return max(m1, m2);
    }
    int query(int l, int r) {
        return query(l, r, 0, 0, size);
    }
};


int N;
vector<int> l, r;

// above[v]: How many of the numbers can have a value above v
// below[v]: How many of the numbers can have a value below v
vector<int> above, below, both;
vector<int> res;
vector<int> ans;

void solve(void)
{
    scanf("%d", &N);

    l.resize(N);
    r.resize(N);
    below.assign(2 * N + 2, 0);
    above.assign(2 * N + 2, 0);
    both.assign(2 * N + 2, 0);
    res.assign(2 * N + 2, -1);
    ans.assign(2 * N + 2, 0);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &l[i], &r[i]);

        below[l[i] + 1]++;
        above[r[i] - 1]++;

        if (l[i] != r[i]) {
            both[l[i] + 1]++;
            both[r[i]]--;
        }
    }

    for (int v = 2 * N; v > 0; v--) {
        above[v] = above[v] + above[v + 1];
    }
    for (int v = 1; v <= 2 * N; v++) {
        below[v] = below[v] + below[v - 1];
    }
    for (int v = 1; v <= 2 * N; v++) {
        both[v] = both[v] + both[v - 1];

        res[v] = above[v] + below[v] - both[v];
    }

    segtree st;
    st.init(res.size());
    st.build(res);
    for (int i = 0; i < N; i++) {
        int opt = st.query(l[i], r[i] + 1);

        if (opt == N) {
            ans[i] = 1;
        }
        else if (opt == N - 1 && l[i] == r[i]) {
            ans[i] = 1;
        }
        else {
            ans[i] = 0;
        }

        printf("%d", ans[i]);
    }
    printf("\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}