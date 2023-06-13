#include <bits/stdc++.h>

#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

struct SegTree {

    int size;
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

    int total(void) {
        return tree[0];
    }

    // Return k-th 1
    int find_kth(int k, int x, int lx, int rx) {
        if (tree[x] < k)
            return -1;
        if (lx == rx - 1)
            return lx;

        int mid = (lx + rx) / 2;

        int ans = find_kth(k, 2 * x + 1, lx, mid);
        if (ans == -1)
            ans = find_kth(k - tree[2 * x + 1], 2 * x + 2, mid, rx);

        return ans;
    }
    int find_kth(int k) {
        return find_kth(k, 0, 0, size);
    }
};

int n, m, q;
SegTree cities;
vector<pi> hosted;
vector<pair<ll, int>> queries;
vector<int> ans;
int myear = 0;

int main(void)
{
    scanf("%d %d %d", &n, &m, &q);

    cities.init(m);
    hosted.resize(m);
    queries.resize(q);
    ans.resize(q);

    for (int i = 0; i < m; i++) {
        hosted[i].s = i;
        hosted[i].f = 0;
    }

    for (int i = 0; i < n; i++) {
        int c;
        scanf("%d", &c);
        hosted[c - 1].f++;

        myear = max(myear, hosted[c - 1].f);
    }
    sort(hosted.begin(), hosted.end());

    for (int i = 0; i < q; i++) {
        scanf("%lld", &queries[i].f);
        queries[i].s = i;
    }
    sort(queries.begin(), queries.end());

    ll year = n;
    int done_already = 0;
    int curmax = hosted.front().f - 1;
    int curnxt = 0;
    ll first_eq = year + 1;

    for (int i = 0; i < m; i++)
        first_eq += myear - hosted[i].f;

    for (int i = 0; i < q; i++) {
        ll t = queries[i].f;

        if (t >= first_eq) {
            ans[queries[i].s] = (t - first_eq) % m;
            continue;
        }

        ll skip = t - year;
        while (cities.total() - done_already < skip) {
            skip -= cities.total() - done_already;
            year += cities.total() - done_already;
            done_already = 0;

            curmax++;
            while (curnxt < m && hosted[curnxt].f == curmax) {
                cities.set(hosted[curnxt].s, 1);
                curnxt++;
            }
        }

        ans[queries[i].s] = cities.find_kth(skip + done_already);
        done_already += skip;
        year = t;

    }

    for (int i = 0; i < q; i++)
        printf("%d\n", ans[i] + 1);

    return 0;
}