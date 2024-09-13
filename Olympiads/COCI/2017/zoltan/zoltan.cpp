#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, ll> pil;

const int MOD = 1e9 + 7;

struct SegTree {
    struct Node {
        int len;
        ll cnt;
    };
    Node DEFAULT = {0, 1};

    Node merge(Node a, Node b) {
        Node res;
        res.len = max(a.len, b.len);
        
        res.cnt = 0;
        if (res.len == a.len) {
            res.cnt += a.cnt;
        }
        if (res.len == b.len) {
            res.cnt += b.cnt;
        }
        res.cnt %= MOD;

        return res;
    }

    int size;
    vector<Node> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, DEFAULT);
    }

    void improve(int i, Node v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = merge(tree[x], v);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            improve(i, v, 2 * x + 1, lx, mid);
        }
        else {
            improve(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void improve(int i, pil v) {
        improve(i, {v.first, v.second}, 0, 0, size);
    }

    Node calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return DEFAULT;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        return merge(calc(l, r, 2 * x + 1, lx, mid), calc(l, r, 2 * x + 2, mid, rx));
    }
    pil calc(int l, int r) {
        Node res = calc(l, r, 0, 0, size);
        return mp(res.len, res.cnt);
    }
};

int N;
vector<int> A;
SegTree st;

vector<int> cords;
vector<ll> pow2;

// increasing[i]/decreasing[i]:
// The longest strictly increasing and decreasing subsequences starting at i and the number of ways to get them
vector<pil> increasing;
vector<pil> decreasing;

int ans = 0;
ll total = 0;

int pos(int x)
{
    return lower_bound(cords.begin(), cords.end(), x) - cords.begin();
}

int main(void)
{
    scanf("%d", &N);

    A.resize(N);
    pow2.resize(N + 1);
    increasing.resize(N);
    decreasing.resize(N);

    pow2[0] = 1;
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        cords.pb(A[i]);

        pow2[i + 1] = pow2[i] * 2 % MOD;
    }
    sort(cords.begin(), cords.end());
    cords.resize(unique(cords.begin(), cords.end()) - cords.begin());

    st.init(N);
    for (int i = N - 1; i >= 0; i--) {
        increasing[i] = st.calc(pos(A[i]) + 1, N);
        increasing[i].first++;
        if (increasing[i].first == 1) {
            increasing[i].second = 1;
        }
        st.improve(pos(A[i]), increasing[i]);
    }
    st.init(N);
    for (int i = N - 1; i >= 0; i--) {
        decreasing[i] = st.calc(0, pos(A[i]));
        decreasing[i].first++;
        if (decreasing[i].first == 1) {
            decreasing[i].second = 1;
        }
        st.improve(pos(A[i]), decreasing[i]);
    }

    ans = 0;
    total = 0;
    for (int i = 0; i < N; i++) {
        int len = increasing[i].first + decreasing[i].first - 1;

        if (len > ans) {
            total = 0;
            ans = len;
        }
        if (len == ans) {
            // First find the number of possible sequences
            ll sequences = increasing[i].second * decreasing[i].second % MOD;

            // The excluded elements can be placed arbitrarily
            int excluded = N - len;
            ll ways = pow2[excluded];

            total += sequences * ways % MOD;
            total %= MOD;
        }
    }

    printf("%d %lld\n", ans, total);

    return 0;
}