#include <bits/stdc++.h>

using namespace std;

struct segtree {

    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int sum(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        int s1 = sum(l, r, 2 * x + 1, lx, mid);
        int s2 = sum(l, r, 2 * x + 2, mid, rx);

        return s1 + s2;
    }
    int sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};

struct query {
    int l, r, id;

    void readquery(int i) {
        id = i;
        scanf("%d %d", &l, &r);
        l--;
    }
};

bool operator < (const query& a, const query& b)
{
    if (a.l == b.l)
        return a.r > b.r;

    return a.l > b.l;
}

int n, q;
vector<int> a;
vector<int> ans;
vector<query> queries;
map<int, int> latest_used;
struct segtree st;

int main(void)
{
    scanf("%d %d", &n, &q);
    a.resize(n);
    queries.resize(q);
    st.init(n);
    ans.resize(q);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < q; i++)
        queries[i].readquery(i);

    sort(queries.begin(), queries.end());

    int curp = 0;
    for (int i = n - 1; i >= 0; i--) {
        // Add the current value to the tree
        if (latest_used.find(a[i]) != latest_used.end())
            st.set(latest_used[a[i]], 0);
        st.set(i, 1);
        latest_used[a[i]] = i;

        // Process all the queries with left endpoint i
        while (curp < q && queries[curp].l == i) {
            ans[queries[curp].id] = st.sum(0, queries[curp].r);
            curp++;
        }
    }

    for (int i = 0; i < ans.size(); i++)
        printf("%d\n", ans[i]);

    return 0;
}