#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;

const int MAXC = 5000;

struct Box {
    int W, H, L;
    int cap;
    int id;

    void readbox(int i) {
        id = i;
        scanf("%d %d %d %d", &H, &W, &L, &cap);
        // if (L < W)
            // swap(L, W);
        if (W < H)
            swap(W, H);
        // if (L < W)
        //     swap(L, W);
    }
};

bool boxsort(const Box& a, const Box& b)
{
    if (a.L == b.L)
        return a.W == b.W ? a.H < b.H : a.W < b.W;

    return a.L < b.L;
}

vector<ll> opt;

struct Bit2D {
    int n, m;
    vector<vector<int>> tree;

    void update(int i, int j, int v) {
        for (int x = i; x < n; x = x | (x + 1))
            for (int y = j; y < m; y = y | (y + 1))
                if (opt[tree[x][y]] < opt[v])
                    tree[x][y] = v;
    }

    int get(int i, int j) {
        int res = 0;
        for (int x = i; x >= 0; x = (x & (x + 1)) - 1)
            for (int y = j; y >= 0; y = (y & (y + 1)) - 1)
                if (opt[res] < opt[tree[x][y]])
                    res = tree[x][y];

        return res;
    }

    void init(int a, int b) {
        n = a;
        m = b;

        tree.resize(n, vector<int>(m, 0));
    }
};

int n, m;
vector<Box> boxes;
Bit2D sq;
vector<int> prv;

int main(void)
{
    scanf("%d", &n);
    boxes.resize(n + 1);
    prv.resize(n + 1);
    opt.assign(n + 1, 0);

    for (int i = 1; i <= n; i++)
        boxes[i].readbox(i);
    boxes[0] = {0, 0, 0, 0};
    sort(boxes.begin(), boxes.end(), boxsort);

    sq.init(MAXC + 1, MAXC + 1);
    for (auto cur : boxes) {
        prv[cur.id] = sq.get(cur.W, cur.H);
        opt[cur.id] = opt[prv[cur.id]] + cur.cap;

        sq.update(cur.W, cur.H, cur.id);
    }

    ll res = 0;
    int last = sq.get(MAXC, MAXC);
    res = opt[last];
    vector<int> ans;
    while (last != 0) {
        ans.push_back(last);
        last = prv[last];
    }

    printf("%lld\n%d\n", res, (int)ans.size());
    for (auto v : ans)
        printf("%d ", v);
    printf("\n");

    return 0;
}