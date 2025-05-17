#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e9;

struct segtree {
    int size;
    
    struct Node {
        ll sum = 0;
        ll ans = -INF;
    };
    Node DEFAULT = {0, -INF};
    vector<Node> tree;

    Node merge(Node a, Node b) {
        Node c;

        c.ans = max(a.ans, a.sum + b.ans);

        c.sum = a.sum + b.sum;

        return c;
    }

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(size * 2, DEFAULT);
    }

    void add(int pos, int val, int x, int l, int r) {
        if (l == r - 1) {
            tree[x].sum += val;
            tree[x].ans = tree[x].sum;
            return;
        }

        int mid = (l + r) / 2;
        if (pos < mid)
            add(pos, val, 2 * x + 1, l, mid);
        else 
            add(pos, val, 2 * x + 2, mid, r);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int pos, int val) {
        add(pos, val, 0, 0, size);
    }

    Node calc(int l, int r, int x, int l_x, int r_x) {
        if (l >= r_x || l_x >= r) {
            // Non intersecting segments
            return DEFAULT;
        }
        if (l <= l_x && r_x <= r) {
            // The query range is fully contained
            return tree[x];
        }

        int mid = (l_x + r_x) / 2;
        auto s1 = calc(l, r, 2 * x + 1, l_x, mid);
        auto s2 = calc(l, r, 2 * x + 2, mid, r_x);

        return merge(s1, s2);
    }
    long long int calc(int l, int r) {
        return calc(l, r, 0, 0, size).ans;
    }

    ll calc2(int l, int r) {
        return calc(l, r, 0, 0, size).sum;
    }
};

int N;
vector<int> A;
segtree beg, fin;
vector<int> b_pos, f_pos;

vector<ll> f_sum;

ll b_sum = 0;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    beg.init(N);
    fin.init(N);
    b_pos.clear();
    f_pos.clear();
    f_sum.clear();

    f_sum.push_back(0);
    b_sum = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        A[i]--;

        beg.add(i, -1);
        fin.add(i, -1);
    }

    for (int i = N - 1; i >= 0; i--) {
        if (fin.calc(A[i], N) + fin.calc2(0, A[i]) < 0) {
            f_pos.push_back(i);
            f_sum.push_back(f_sum.back() + i);
            fin.add(A[i], 1);
        }
    }

    ll ans = 0;

    for (int i = 0; i < N - 1; i++) {
        if (beg.calc(A[i], N) + beg.calc2(0, A[i]) < 0) {
            b_pos.push_back(i);
            b_sum += -i;
            beg.add(A[i], 1);
        }

        if (f_pos.back() == i) {
            // Remove i
            f_pos.pop_back();
            f_sum.pop_back();
            fin.add(A[i], -1);
        }

        while (b_pos.size() > f_pos.size()) {
            int j = b_pos.back();
            b_sum -= -j;
            beg.add(A[j], -1);

            b_pos.pop_back();
        }

        int s = b_pos.size();
        ans = max(ans, f_sum[s] + b_sum);
    }

    printf("%lld\n", ans);

}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}