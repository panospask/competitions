#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const ll INF = 1e18;

struct SegTree {
    int size;
    vector<ll> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, INF);
    }

    void apply(int i, ll v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = min(tree[x], v);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            apply(i, v, 2 * x + 1, lx, mid);
        }
        else {
            apply(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void apply(int i, ll v) {
        apply(i, v, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return INF;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ll c1 = calc(l, r, 2 * x + 1, lx, mid);
        ll c2 = calc(l, r, 2 * x + 2, mid, rx);

        return min(c1, c2);
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

struct Slingshot {
    int x, y, t;

    ll total_add(bool x_aft, bool y_aft)
    {
        ll res = t;
        if (!x_aft) {
            res -= x;
        }
        else {
            res += x;
        }

        if (!y_aft) {
            res -= y;
        }
        else {
            res += y;
        }

        return res;
    }
};
bool operator < (const Slingshot& a, const Slingshot& b)
{
    return a.x < b.x;
}

struct Query {
    int a, b, id;
};
bool operator < (const Query& a, const Query& b)
{
    return a.a < b.a;
}

int N, M;
vector<Query> queries;
vector<Slingshot> slingshots;
vector<int> start_cord;
vector<int> end_cord;
vector<ll> ans;
SegTree st[2];

int code(int x)
{
    return lower_bound(end_cord.begin(), end_cord.end(), x) - end_cord.begin();
}

void codify(vector<int>& v)
{
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
}

void makemin(ll& a, ll b)
{
    a = min(a, b);
}

int main(void)
{
    freopen("slingshot.in", "r", stdin);
    freopen("slingshot.out", "w", stdout);

    scanf("%d %d", &N, &M);

    slingshots.resize(N);
    queries.resize(M);
    ans.assign(M, INF);

    for (int i = 0; i < N; i++) {
        int x, y, t;
        scanf("%d %d %d", &x, &y, &t);
        slingshots[i] = {x, y, t};

        start_cord.pb(x);
        end_cord.pb(y);
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        queries[i] = {a, b, i};
        ans[i] = abs(a - b);

        start_cord.pb(a);
        end_cord.pb(b);
    }

    codify(start_cord);
    codify(end_cord);

    st[0].init(end_cord.size());
    st[1].init(end_cord.size());

    sort(slingshots.begin(), slingshots.end());
    sort(queries.begin(), queries.end());

    int p1 = 0;
    int p2 = 0;
    for (int i = 0; i < start_cord.size(); i++) {
        while (p1 < N && slingshots[p1].x <= start_cord[i]) {
            st[0].apply(code(slingshots[p1].y), slingshots[p1].total_add(0, 0));
            st[1].apply(code(slingshots[p1].y), slingshots[p1].total_add(0, 1));
            p1++;
        }
        while (p2 < M && queries[p2].a <= start_cord[i]) {
            int id = queries[p2].id;
            int end_p = code(queries[p2].b);
            int end_v = queries[p2].b;

            makemin(ans[id], queries[p2].a + min(st[0].calc(0, end_p + 1) + end_v, st[1].calc(end_p, end_cord.size()) - end_v));

            p2++;
        }
    }

    st[0].init(end_cord.size());
    st[1].init(end_cord.size());

    p1 = N - 1;
    p2 = M - 1;
    for (int i = start_cord.size() - 1; i >= 0; i--) {
        while (p1 >= 0 && slingshots[p1].x >= start_cord[i]) {
            st[0].apply(code(slingshots[p1].y), slingshots[p1].total_add(1, 0));
            st[1].apply(code(slingshots[p1].y), slingshots[p1].total_add(1, 1));

            p1--;
        }
        while (p2 >= 0 && queries[p2].a >= start_cord[i]) {
            int id = queries[p2].id;
            int end_p = code(queries[p2].b);
            int end_v = queries[p2].b;

            makemin(ans[id], -queries[p2].a + min(st[0].calc(0, end_p + 1) + end_v, st[1].calc(end_p, end_cord.size()) - end_v));

            p2--;
        }
    }

    for (int i = 0; i < M; i++) {
        printf("%lld\n", ans[i]);
    }

    return 0;
}