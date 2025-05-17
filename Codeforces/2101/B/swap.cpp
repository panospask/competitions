#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

struct segtree {

    vector<long long int> tree;
    int size;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(size * 2, 0LL);
    }

    void build(vector<int>& a, int x, int l_x, int r_x) {
        if (l_x == r_x - 1) {
            if (l_x < a.size())
                tree[x] = a[l_x];
            else 
                tree[x] = 0;

            return;
        }

        int mid = (l_x + r_x) / 2;
        build(a, 2 * x + 1, l_x, mid);
        build(a, 2 * x + 2, mid, r_x);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void set(int pos, int val, int x, int l, int r) {
        if (l == r - 1) {
            tree[x] = val;
            return;
        }

        int mid = (l + r) / 2;
        if (pos < mid)
            set(pos, val, 2 * x + 1, l, mid);
        else 
            set(pos, val, 2 * x + 2, mid, r);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void set(int pos, int val) {
        set(pos, val, 0, 0, size);
    }

    long long int calc(int l, int r, int x, int l_x, int r_x) {
        if (l >= r_x || l_x >= r) {
            // Non intersecting segments
            return 0;
        }
        if (l <= l_x && r_x <= r) {
            // The query range is fully contained
            return tree[x];
        }

        int mid = (l_x + r_x) / 2;
        auto s1 = calc(l, r, 2 * x + 1, l_x, mid);
        auto s2 = calc(l, r, 2 * x + 2, mid, r_x);

        return s1 + s2;
    }
    long long int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N;
vector<int> A;
vector<int> idx;
segtree st;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    idx.resize(2 * N);
    st.init(2 * N);

    vector<int> odds;
    vector<int> evens;
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        A[i]--;
    }

    sort(odds.rbegin(), odds.rend());
    sort(evens.rbegin(), evens.rend());

    vector<int> ans;
    int time = 0;
    while (time < N-  3) {
        int v = -1;
        if (time % 2) {
            v = odds.back();
            odds.pop_back();
        }
        else {
            v = evens.back();
            evens.pop_back();
        }

        int p = st.calc(0, idx[v]) + time;

        if (p == N - 1) {
            // Do something
        }

        
    }
}

int main(void) {
    ;
}