#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pi;

struct SegTree {
    const ll NO_OP = 0;
    const ll NEUTRAL = LONG_LONG_MAX;

    int size;
    vector<ll> op;
    vector<ll> tree;

    void init(int N) {
        size = 1;
        while (size < N)
            size *= 2;

        tree.assign(2 * size, 0);
        op.assign(2 * size, NO_OP);
    }

    void propagate(int x) {
        op[2 * x + 1] += op[x];
        op[2 * x + 2] += op[x];
        tree[2 * x + 1] += op[x];
        tree[2 * x + 2] += op[x];

        op[x] = NO_OP;
    }

    void add(int l, int r, ll v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            op[x] += v;
            tree[x] += v;
            return;
        }

        propagate(x);
        int mid = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, mid);
        add(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int l, int r, ll v) {
        add(l, r, v, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x);
        int mid = (lx + rx) / 2;

        return min(calc(l, r, 2 * x + 1, lx, mid),  calc(l, r, 2 * x + 2, mid, rx));
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N, L;
vector<ll> heights;
vector<ll> width_pref;
stack<pi> best;

// st(i): Cost to photograph everything up to i in one photo and everything else after
SegTree st;

// dp[i]: Minimum cost to fully photograph all buildings up to i
vector<ll> dp;

int main(void)
{
    freopen("nytrip.in", "r", stdin);
    freopen("nytrip.out", "w", stdout);

    scanf("%d %d", &N, &L);

    heights.resize(N + 1);
    width_pref.resize(N + 1);
    st.init(N + 2);
    dp.resize(N + 1);

    heights[0] = width_pref[0] = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%lld %lld", &heights[i], &width_pref[i]);
        width_pref[i] += width_pref[i - 1];
    }

    dp[0] = 0;
    st.add(0, 1, 0);
    best.push(mp(0, 0));
    for (int i = 1; i <= N; i++) {
        st.add(i - 1, i, heights[i]);
        int cur = i - 1;

        while (!best.empty() && best.top().first < heights[i]) {
            // Update everything from cur - 1 to best.top.second()
            st.add(best.top().second, cur, heights[i] - best.top().first);
            cur = best.top().second;

            best.pop();
        }

        int earliest = lower_bound(width_pref.begin(), width_pref.end(), width_pref[i] - L) - width_pref.begin();
        dp[i] = st.calc(earliest, i);

        st.add(i, i + 1, dp[i]);
        best.push(mp(heights[i], cur));
    }

    printf("%lld\n", dp[N]);
}