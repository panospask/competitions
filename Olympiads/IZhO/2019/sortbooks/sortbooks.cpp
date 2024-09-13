#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e9 + 1;

struct SegTree {
    int size;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, -INF);
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
        if (lx >= r || l >= rx) {
            return -INF;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;

        return max(calc(l, r, 2 * x + 1, lx, mid), calc(l, r, 2 * x + 2, mid, rx));
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

struct Query {
    int l, r, k;

    int id;
};

bool querysort(Query a, Query b) 
{
    return a.l > b.l;
}

int N, M;
vector<int> w;
vector<Query> queries;
vector<int> ans;
SegTree st;
SegTree vals;

int invcomp(int a, int b)
{
    return a > b;
}

// Get last place in local maximum array that is BEFORE r
int getlast(int r, vector<int>& s)
{
    int pos = upper_bound(s.begin(), s.end(), r, invcomp) - s.begin();

    return s[pos];
}

int main(void)
{
    scanf("%d %d", &N, &M);

    w.resize(N);
    st.init(N + 1);
    vals.init(N + 1);
    queries.resize(M);
    ans.resize(M);

    for (int i = 0; i < N; i++) {
        scanf("%d", &w[i]);
    }
    w.pb(INF);

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &queries[i].l, &queries[i].r, &queries[i].k);
        queries[i].l--;
        queries[i].id = i;
    }
    sort(queries.begin(), queries.end(), querysort);

    vector<int> s;
    s.pb(N);
    int p = 0;
    for (int i = N - 1; i >= 0; i--) {
        while (w[s.back()] < w[i]) {
            vals.set(s.back(), -INF);
            s.pop_back();
        }
        st.set(i, w[i]);

        int curopt = st.calc(i + 1, s.back());
        if (curopt >= 0) {
            curopt += w[i];
        }
        vals.set(i, curopt);
        s.pb(i);

        while (p < M && queries[p].l == i) {
            Query cur = queries[p];

            int pos = getlast(cur.r, s);
            int res = vals.calc(cur.l, pos);
            if (pos + 1 != cur.r) {
                res = max(res, st.calc(pos + 1, cur.r) + w[pos]);
            }

            ans[cur.id] = res <= cur.k;

            p++;
        }
    }

    for (int i = 0; i < M; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}