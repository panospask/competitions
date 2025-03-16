#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int INF = 1e9;

struct Node {
    Node() : value(INF), times(0) {};
    Node(int v, ll t) : value(v), times(t) {};

    int value;
    ll times;
};

Node merge(Node a, Node b) {
    if (a.value == b.value) {
        return Node(a.value, (a.times + b.times) % MOD);
    }
    else if (a.value < b.value) {
        return a;
    }
    else {
        return b;
    }
}

struct SegTree {
    int size;
    vector<Node> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, Node());
    }

    void set(int i, Node n, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = n;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            set(i, n, 2 * x + 1, lx, mid);
        }
        else {
            set(i, n, 2 * x + 2, mid, rx);
        }

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, Node n) {
        set(i, n, 0, 0, size);
    }

    Node calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return Node();
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        Node n1 = calc(l, r, 2 * x + 1, lx, mid);
        Node n2 = calc(l, r, 2 * x + 2, mid, rx);

        return merge(n1, n2);
    }
    Node calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N, M;
vector<int> a, b;
vector<ll> pref;

// dp[k][i]: Minimum way to remove the first i numbers and have the value of k mentioned
vector<SegTree> dp;

void solve(void) {
    scanf("%d %d", &N, &M);

    a.resize(N);
    b.resize(M);
    pref.resize(N + 1);

    pref[0] = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        pref[i + 1] = pref[i] + a[i];
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &b[i]);
    }

    dp.resize(M);
    for (int k = 0; k < M; k++) {
        dp[k].init(N + 1);
        dp[k].set(0, Node(0, 1));
    }

    for (int k = 0; k < M; k++) {
        for (int i = 1; i <= N; i++) {
            Node cur;
            if (k != 0) {
                cur = dp[k - 1].calc(i, i + 1);
            }

            // Find how much backwards we can go with b[k] total
            int j = lower_bound(pref.begin(), pref.end(), pref[i] - b[k]) - pref.begin();

            // Use all the positions in the allowed range
            Node prv = dp[k].calc(j, i);
            prv.value += M - k - 1;
            cur = merge(cur, prv);
            dp[k].set(i, cur);
        }
    }

    Node ans = dp[M - 1].calc(N, N + 1);

    if (ans.value == INF) {
        printf("-1\n");
    }
    else {
        printf("%d %lld\n", ans.value, ans.times);
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}