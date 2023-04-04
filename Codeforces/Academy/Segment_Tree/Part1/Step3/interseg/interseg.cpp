#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int n;

struct segtree {

    int size = 1;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n) 
            size *= 2;
        
        tree.assign(2 * size, 0);
    }

    void build(int *a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < n)
                tree[x] = a[lx];
            else 
                tree[x] = 0;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void build(int* a) {
        build(a, 0, 0, size);
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
        int s1 = calc(l, r, 2 * x + 1, lx, mid);
        int s2 = calc(l, r, 2 * x + 2, mid, rx);

        return s1 + s2;
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int ans[MAXN + 2];
int p[2 * MAXN + 2];
int visited[MAXN + 2];

void calc_answers(void) 
{
    segtree st;
    st.init(n);

    for (int i = 0; i < n; i++)
        visited[i] = -1;

    int curpos = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (visited[p[i]] == -1) {
            visited[p[i]] = curpos++;
            st.set(visited[p[i]], 1);
        }
        else {
            st.set(visited[p[i]], 0);
            ans[p[i]] += st.calc(visited[p[i]], n);
        }
    }
}

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < 2 * n; i++) {
        scanf("%d", &p[i]);
        p[i]--;
    }

    calc_answers();
    reverse(p, p + 2 * n);
    calc_answers();

    for (int i = 0; i < n; i++)
        printf("%d ", ans[i]);
    printf("\n");

    return 0;
}
