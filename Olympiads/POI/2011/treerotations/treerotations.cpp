#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

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

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            add(i, v, 2 * x + 1, lx, mid);
        else
            add(i, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    int sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
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
};

int N;
ll ans = 0;
vector<int> sz;
vector<vector<int>> adj_list;
vector<bool> isleaf;
vector<int> v;
SegTree st;

vector<int> tin;
vector<int> tout;
vector<int> trav;
int counter;

void CalcAnswer(int node, bool isheavy)
{
    if (isleaf[node]) {
        if (isheavy)
            st.add(v[node], 1);
        return;
    }

    int c1 = adj_list[node][0];
    int c2 = adj_list[node][1];
    if (sz[c1] > sz[c2]) {
        swap(c1, c2);
    }

    CalcAnswer(c1, false);
    CalcAnswer(c2, true);

    // Check if it optimal to have c1 or c2 first
    ll add1 = 0;
    ll add2 = 0;
    for (int t = tin[c1]; t < tout[c1]; t++) {
        int cur = trav[t];

        if (isleaf[cur]) {
            add1 += st.sum(0, v[cur]);
            add2 += st.sum(v[cur] + 1, st.size);
        }
    }

    ans += min(add1, add2);
    for (int t = tin[c1]; t < tout[c1]; t++) {
        int cur = trav[t];

        if (isleaf[cur]) {
            st.add(v[cur], 1);
        }
    }

    if (!isheavy) {
        for (int t = tin[node]; t < tout[node]; t++) {
            int cur = trav[t];

            if (isleaf[cur]) {
                st.add(v[cur], -1);
            }
        }
    }
}

void ReadNode(int node)
{
    int num;
    scanf("%d", &num);
    N++;
    sz[node] = 1;

    tin[node] = counter++;
    trav[tin[node]] = node;

    if (num == 0) {
        adj_list[node].pb(N);
        ReadNode(N);
        sz[node] += sz[adj_list[node].back()];

        adj_list[node].pb(N);
        ReadNode(N);
        sz[node] += sz[adj_list[node].back()];
    }
    else {
        v[node] = num;
        isleaf[node] = true;
    }

    tout[node] = counter;
}

int main(void)
{
    scanf("%d", &N);
    st.init(N + 1);

    N += N - 1;

    adj_list.resize(N);
    sz.resize(N);
    isleaf.assign(N, false);
    v.resize(N);
    tin.resize(N);
    tout.resize(N);
    trav.resize(N);


    N = 0;
    ReadNode(0);

    CalcAnswer(0, true);

    printf("%lld\n", ans);

    return 0;
}