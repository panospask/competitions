#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

const int INF = 1e6;
typedef pair<int, int> pi;

struct SegTree {
    int size;
    int ttl = 0;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, 0);
    }

    void set(int i, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = 1;
            ttl++;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            set(i, 2 * x + 1, lx, mid);
        }
        else {
            set(i, 2 * x + 2, mid, rx);
        }

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void set(int i) {
        set(i, 0, 0, size);
    }

    int sum(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        return sum(l, r, 2 * x + 1, lx, mid) + sum(l, r, 2 * x + 2, mid, rx);
    }
    int sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }

    int kth(int k, int x, int lx, int rx) {
        if (k == 0) {
            return -1;
        }
        if (tree[x] < k) {
            return -1;
        }
        else if (lx == rx - 1) {
            return lx;
        }

        int mid = (lx + rx) / 2;
        int ans = kth(k, 2 * x + 1, lx, mid);
        if (ans == -1) {
            ans = kth(k - tree[2 * x + 1], 2 * x + 2, mid, rx);
        }

        return ans;
    }
    int kth(int k) {
        return kth(k, 0, 0, size);
    }

    pi range(int i) {
        int s = sum(0, i);
        return mp(kth(s), kth(s + 1));
    }
};

typedef pair<int, int> pi;

int N;
string s;
vector<vector<int>> z;
vector<int> ans;

// first[i][len]: True iff the substr [i..i+len] first appears at i
vector<vector<bool>> able;

void zcalc(int t, vector<int>& z)
{
    z.assign(N, 0);
    int l = t, r = t;

    for (int i = t + 1; i < N; i++) {
        if (i < r) {
            z[i] = min(r - i, z[i - l + t]);
        }

        while (i + z[i] < N && s[i + z[i]] == s[t + z[i]]) {
            z[i]++;
        }

        if (i + z[i] > r) {
            r = i + z[i];
            l = i;
        }

        able[i][z[i]] = false;
    }

    z[t] = N - t;
}

void propagate(void)
{
    for (int i = 0; i < N; i++) {
        for (int len = N - 1; len >= 0; len--) {
            able[i][len] = able[i][len] && able[i][len + 1];
        }
    }
}

void calculate(int source, vector<int>& z)
{
    vector<pi>  idx;
    SegTree used;
    used.init(N);

    // modify[len]: How much to modify when switching from len + 1 to len
    vector<int> md(N + 2, 0);

    for (int i = source; i < N; i++) {
        idx.pb(mp(z[i], i));
    }
    sort(idx.rbegin(), idx.rend());

    int components = N;
    int p = 0;
    for (int len = N - source; len > 1; len--) {
        if (!able[source][len]) {
            break;
        }

        md[len] += md[len + 1];
        components += md[len];
        components += used.ttl;
        while (p < idx.size() && idx[p].first == len) {
            int i = idx[p].second;
            p++;

            // Insert i into the usable thingies
            components -= len - 1;

            // Find relationship with previous and with next
            int prv, nxt;
            tie(prv, nxt) = used.range(i);
            if (nxt != -1) {
                int newlen = nxt - i + 1;
                if (len > newlen) {
                    components += len - newlen;
                    md[len - 1]--;
                    md[newlen - 1]++;
                }
            }

            if (prv != -1) {

                int newlen = i - prv + 1;
                if (len > newlen) {
                    components += len - newlen;
                    md[len - 1]--;
                    md[newlen - 1]++;
                }
            }

            used.set(i);
        }

        ans[components] = min(ans[components], len);
    }
}

int main(void)
{
    cin >> s;
    N = s.size();
    z.resize(N);
    able.assign(N, vector<bool>(N + 1, true));

    for (int i = 0; i < N; i++) {
        zcalc(i, z[i]);
    }
    propagate();

    ans.assign(N + 1, INF);
    for (int i = 0; i < N; i++) {
        calculate(i, z[i]);
    }

    ans[N] = 1;
    for (int i = 1; i <= N; i++) {
        if (ans[i] == INF) {
            ans[i] = 0;
        }
        printf("%d ", ans[i]);
    }
    printf("\n");

    return 0;
}