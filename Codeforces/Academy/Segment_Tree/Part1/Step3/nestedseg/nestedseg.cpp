#include <bits/stdc++.h>
#define SINGLE_ELEMENT(i) (make_pair(i, 1))
#define MAXN 100000

using namespace std;

typedef pair<int, int> ii;
ii NULL_ELEMENT = make_pair(INT_MIN, 0);

ii merge(ii a, ii b) 
{
    if (a.first > b.first)
        return a;
    else if (b.first > a.first)
        return b;
    else
        return make_pair(a.first, a.second + b.second);
}

int n;

struct segtree {

    int size = 1;
    vector<ii> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(size * 2, make_pair(0,0));
    }

    void build(int* a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < n)
                tree[x] = SINGLE_ELEMENT(a[lx]);
            else 
                tree[x] = NULL_ELEMENT;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x  + 1], tree[2 * x + 2]);
    }
    void build(int* a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = SINGLE_ELEMENT(v);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else 
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    ii calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            // Disjoint segments
            return NULL_ELEMENT;
        }
        if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ii c1 = calc(l, r, 2 * x + 1, lx, mid);
        ii c2 = calc(l, r, 2 * x + 2, mid, rx);

        return merge(c1, c2);
    }
    ii calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

segtree st;
int ans[MAXN + 2];
int place[MAXN + 2];

int main(void)
{
    scanf("%d", &n);
    int curplace = 0;
    for (int i = 0; i < n; i++) { 
        place[i] = -1;
    }
    st.init(n);

    int v;
    for (int i = 0; i < 2 * n; i++) {
        scanf("%d", &v);
        v--;
        
        if (place[v] == -1) {
            place[v] = curplace++;
            st.set(place[v], 1);
        }
        else {
            auto res = st.calc(place[v], n);
            if (res.first == 2)
                ans[v] = res.second;
            else 
                ans[v] = 0;

            st.set(place[v], 2);
        }
    }

    for (int i = 0; i < n; i++)
        printf("%d ", ans[i]);
    printf("\n");

    return 0;
}