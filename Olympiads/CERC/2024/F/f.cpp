#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;
typedef pair<ll, ll> pll;

// CHANGE BEFORE SUBMIT
const ll MAXR = 200010;

struct SegTree {
    ll size;
    vector<ll> tree;
    vector<ll> lazy;

    void init(ll N) {
        size = 1;
        while (size < N) {
            size = 2 * size;
        }
        tree.assign(2 * size, 0);
        lazy.assign(2 * size, 0);
    }

    void propagate(ll x) {
        if (lazy[x] == 0) {
            return;
        }

        tree[2 * x + 1] = lazy[x];
        tree[2 * x + 2] = lazy[x];
        lazy[2 * x + 1] = lazy[x];
        lazy[2 * x + 2] = lazy[x];
        lazy[x] = 0;
    }

    void set(ll l, ll r, ll v, ll x, ll lx, ll rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        if (l <= lx && rx <= r) {
            lazy[x] = v;
            tree[x] = v;
            return;
        }

        propagate(x);
        
        ll mid = (lx + rx) / 2;
        set(l, r, v, 2 * x + 1, lx, mid);
        set(l, r, v, 2 * x + 2, mid, rx);
        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(ll l, ll r, ll v) {
        set(l, r, v, 0, 0, size);
    }

    ll calc(ll l, ll r, ll x, ll lx, ll rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x);

        ll mid = (lx + rx) / 2;
        ll c1 = calc(l, r, 2 * x + 1, lx, mid);
        ll c2 = calc(l, r, 2 * x + 2, mid, rx);
        return max(c1, c2);
    }
    ll calc(ll l, ll r) {
        return calc(l, r, 0, 0, size);
    }
};

ll N;
vector<pll> blocks;
vector<ll> h;

SegTree st;

unordered_map<ll, vector<pll>> up, down;
vector<vector<pll>> lft, rght;

ll ans = 0;

void compress(vector<pll>& v) {
    // Merge adjacent ranges in v2
    vector<pll> v_opt;
    for (auto [l, r] : v) {
        if (!v_opt.empty() && v_opt.back().second == l) {
            v_opt.back().second = r;
        }
        else {
            v_opt.push_back({l, r});
        }
    }
    v = v_opt;
}

void calculate(void) {
    for (auto& [x, v1] : down) {
        auto v2 = up[x];
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());

        compress(v1);
        compress(v2);

        // Iterate over down edges, they are the responsible ones

        // Where are we in the up array (current j is the first one s.t its r is >= than previous i's r)
        // [meaning it can be possibly used for us]
        ll j = 0;

        // prv is 1 iff we have a a wall before (for possible merges)
        ll prv = 0;
        for (ll i = 0; i < v1.size(); i++) {
            ll l = v1[i].first;
            ll r = v1[i].second;
            
            // We can't continue from before. Check for new indices right wall
            prv = 0;

            while (j < v2.size() && v2[j].second <= l) j++;


            // In theory this should return the segment that starts **before** x
            ll pos = lower_bound(rght[l].begin(), rght[l].end(), (pll){x, -1}) - rght[l].begin() - 1;
            if (pos != -1 && rght[l][pos].second >= x) {
                // We found a previous wall
                prv = 1;
            }

            while (j < v2.size()) {
                // Check if we can use the left endpoll with our existing r
                if (prv && v2[j].first >= l && v2[j].first <= r) {
                    ans++;
                }
                if (max(l, v2[j].first) <= min(r, v2[j].second)) {
                    prv = 0;
                }

                // We can use the right wall as a left enclosure wall
                if (v2[j].second < r) {
                    prv = 1;
                    j++;
                }
                else {
                    break;
                }
            }

            // Also check if we can find a right wall to merge with the left
            pos = lower_bound(lft[r].begin(), lft[r].end(), (pll){x, -1}) - lft[r].begin() - 1;
            if (pos != -1 && lft[r][pos].second >= x) {
                // We found a next wall
                if (prv) {
                    ans++;
                }
            }
        }
    }
}

int main(void) {
    scanf("%d", &N);

    blocks.resize(N);
    h.resize(N);
    st.init(MAXR);
    lft.resize(MAXR);
    rght.resize(MAXR);

    for (ll i = 0; i < N; i++) {
        scanf("%lld %lld %lld", &blocks[i].first, &blocks[i].second, &h[i]);

        // [l, r)
        // Find base height and insert back llo st
        ll base = st.calc(blocks[i].first, blocks[i].second);
        st.set(blocks[i].first, blocks[i].second, base + h[i]);

        down[base].push_back({blocks[i].first, blocks[i].second});
        up[base + h[i]].push_back({blocks[i].first, blocks[i].second});
        lft[blocks[i].first].push_back({base, base + h[i]});
        rght[blocks[i].second].push_back({base, base + h[i]});
    }

    for (int i = 0; i < MAXR; i++) {
        sort(lft[i].begin(), lft[i].end());
        sort(rght[i].begin(), rght[i].end());
    }

    calculate();

    printf("%lld\n", ans);
}