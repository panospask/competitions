#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    const int DEFAULT = 0;
    int size;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
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

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        return calc(l, r, 2 * x + 1, lx, mid) + calc(l, r, 2 * x + 2, mid, rx);
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

struct Query {
    int l, r;
    int id;
};
bool operator < (const Query& a, const Query& b)
{
    return a.r < b.r;
}

int N, Q;
SegTree st;
vector<int> a;
unordered_map<int, int> latest;
vector<Query> queries;
vector<int> ans;

int main(void)
{
    scanf("%d %d", &N, &Q);

    a.resize(N);
    ans.resize(Q);
    queries.resize(Q);
    st.init(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < Q; i++) {
        scanf("%d %d", &queries[i].l, &queries[i].r);
        queries[i].l--;
        queries[i].r--;
        queries[i].id = i;
    }
    sort(queries.begin(), queries.end());

    int q_p = 0;
    for (int i = 0; i < N; i++) {
        while (q_p < Q && queries[q_p].r < i) {
            ans[queries[q_p].id] = st.calc(queries[q_p].l, i);
            q_p++;
        }

        if (latest.count(a[i])) {
            st.set(latest[a[i]], 0);
        }
        latest[a[i]] = i;
        st.set(i, 1);
    }
    while (q_p < Q) {
        ans[queries[q_p].id] = st.calc(queries[q_p].l, N);
        q_p++;
    }

    for (int i = 0; i < Q; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}