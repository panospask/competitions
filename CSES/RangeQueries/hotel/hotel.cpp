#include <bits/stdc++.h>

using namespace std;

struct segtree {

    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(size * 2);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = a[lx];
            else
                tree[x] = 0;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            add(i, v, 2 * x + 1, lx, mid);
        else
            add(i, v, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    int find_first_greater(int k, int x, int lx, int rx) {
        if (tree[x] < k)
            return -1;

        if (lx == rx - 1)
            return lx;

        int mid = (lx + rx) / 2;
        int ans = find_first_greater(k, 2 * x + 1, lx, mid);
        if (ans == -1)
            ans = find_first_greater(k, 2 * x + 2, mid, rx);

        return ans;
    }
    int find_first_greater(int k) {
        return find_first_greater(k, 0, 0, size);
    }
};

int n, m;
vector<int> rooms;
segtree st;

int main(void)
{
    scanf("%d %d", &n, &m);
    rooms.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &rooms[i]);

    st.init(n);
    st.build(rooms);

    while (m--) {
        int request;
        scanf("%d", &request);
        int pos = st.find_first_greater(request);
        if (pos != -1) {
            printf("%d ", pos + 1);
            st.add(pos, -request);
        }
        else {
            printf("0 ");
        }
    }
    printf("\n");

    return 0;
}