#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

struct SegTree {
    struct Node {
        int total;
        int max;
    };
    Node NEUTRAL = {0, 0};

    Node create(int v) {
        return {v, max(0, v)};
    }

    Node merge(Node& a, Node& b) {
        Node c;
        c.total = a.total + b.total;
        c.max = max(a.max, a.total + b.max);

        return c;
    }

    int size;
    vector<Node> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, NEUTRAL);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = create(v);
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

    int getmax(void) {
        return max(0, tree[0].max);
    }
};

int n;
vector<int> elsiecards;
unordered_map<int, bool> have_elsie;
vector<int> bessiecards;

SegTree high, low;

int main(void)
{
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    scanf("%d", &n);
    elsiecards.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &elsiecards[i]);
        have_elsie[elsiecards[i]] = true;
    }
    for (int c = 1; c <= 2 * n; c++)
        if (!have_elsie[c])
            bessiecards.push_back(c);

    reverse(bessiecards.begin(), bessiecards.end());

    assert(bessiecards.size() == n && elsiecards.size() == n);

    high.init(2 * n);
    low.init(2 * n);
    // First, what if the game only plays in low card mode
    int ans = 0;
    for (int i = 0; i < n; i++) {
        low.set(2 * n - elsiecards[i], -1);
        low.set(2 * n - bessiecards[i], 1);
    }
    ans = max(0, n - low.getmax());

    for (int i = 0; i < n; i++) {
        // Transfer the i-th card over to high card mode
        high.set(elsiecards[i] - 1, -1);
        high.set(bessiecards[i] - 1, 1);
        low.set(2 * n - elsiecards[i], 0);
        low.set(2 * n - bessiecards[i], 0);

        ans = max(ans, n - low.getmax() - high.getmax());
    }

    printf("%d\n", ans);

    return 0;
}