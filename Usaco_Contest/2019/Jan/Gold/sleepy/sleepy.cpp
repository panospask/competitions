#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;


struct segtree {

    int size = 1;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;
        tree.assign(2 * size, 0);
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
        if (l >= rx || lx >= r) {
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

int n;
vector<int> cows;
segtree st;

int main(void)
{
    freopen("sleepy.in", "r", stdin);
    freopen("sleepy.out", "w", stdout);

    scanf("%d", &n);
    cows.resize(n);
    st.init(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &cows[i]);
        cows[i]--;
    }

    int sortstart = 0;
    for (int i = 1; i < n; i++)
        if (cows[i] < cows[i-1])
            sortstart = i;

    // The sorted order starts from sortstart
    for (int i = sortstart; i < n; i++)
        st.set(cows[i], 1);

    int steps = sortstart;
    printf("%d\n", steps);
    for (int i = 0; i < steps; i++) {
        int v = cows[i];
        int move = sortstart + st.sum(0, v) - 1;
        printf("%d", move);
        if (i != steps - 1)
            printf(" ");

        st.set(v, 1);
        sortstart--;
    }
    printf("\n");

    return 0;
}