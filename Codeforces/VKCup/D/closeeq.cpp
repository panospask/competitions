#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct SegTree {
    const int NEUTRAL = INT_MAX;

    int size;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N)
            size *= 2;

        tree.assign(2 * size, INT_MAX);
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

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;

        return min(calc(l, r, 2 * x + 1, lx, mid), calc(l, r, 2 * x + 2, mid, rx));
    }
    int calc(int l, int r) {
        int v = calc(l, r, 0, 0, size);
        return v != INT_MAX ? v : -1;
    }
};

int n, q;
vector<int> a;
vector<int> ans;
vector<int> values;
vector<int> latest_oc;
vector<pair<pi, int>> queries;

SegTree st;

int find(int v)
{
    return lower_bound(values.begin(), values.end(), v) - values.begin();
}

void compress(void)
{
    for (int i = 0; i < n; i++)
        values.pb(a[i]);

    sort(values.begin(), values.end());
    values.resize(unique(values.begin(), values.end()) - values.begin());

    for (int i = 0; i < n; i++)
        a[i] = find(a[i]);

    latest_oc.assign(values.size(), -1);
}

int main(void)
{
    scanf("%d %d", &n, &q);
    a.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    compress();

    st.init(n);
    queries.resize(q);
    ans.resize(q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &queries[i].first.first, &queries[i].first.second);
        queries[i].first.first--;
        queries[i].first.second--;
        queries[i].second = i;
    }

    sort(queries.begin(), queries.end(), [] (pair<pi, int> a, pair<pi, int> b) {return a.first.second < b.first.second;});

    int curp = 0;
    for (int i = 0; i < n; i++) {
        if (latest_oc[a[i]] != -1)
            st.set(latest_oc[a[i]], i - latest_oc[a[i]]);
        latest_oc[a[i]] = i;

        while (curp < q && queries[curp].first.second == i) {
            ans[queries[curp].second] = st.calc(queries[curp].first.first, i + 1);
            curp++;
        }
    }

    for (int i = 0; i < q; i++)
        printf("%d\n", ans[i]);

    return 0;
}