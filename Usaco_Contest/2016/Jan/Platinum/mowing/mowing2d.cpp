#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct SegTree {
    const int NEUTRAL = 0;

    struct Node {
        int val;
        Node* l, *r;

        Node(int a, Node* b, Node* c) : val(a), l(b), r(c) {};
    };
    int size;
    Node* root,* null;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        null = new Node(0, nullptr, nullptr);
        null->l = null->r = null;
        root = new Node(0, null, null);
    }

    Node* add(int i, int v, Node* x, int lx, int rx) {
        if (x == null) {
            x = new Node(0, null, null);
        }
        if (lx == rx - 1) {
            x->val += v;
            return x;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            x->l = add(i, v, x->l, lx, mid);
        else
            x->r = add(i, v, x->r, mid, rx);

        x->val = x->l->val + x->r->val;
        return x;
    }
    void add(int i, int v) {
        if (i < size && i >= 0)
            root = add(i, v, root, 0, size);
    }

    int calc(int l, int r, Node* x, int lx, int rx) {
        if (x == null)
            return NEUTRAL;
        if (l >= rx || lx >= r) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return x->val;
        }

        int mid = (lx + rx) / 2;
        int c1 = calc(l, r, x->l, lx, mid);
        int c2 = calc(l, r, x->r, mid, rx);
        return c1 + c2;
    }
    int calc(int l, int r) {
        return calc(l, r, root, 0, size);
    }
};

struct BITree {
    int size;
    vector<SegTree> tree;

    void init(int n, int m) {
        size = n;
        tree.resize(n);
        for (int i = 0; i < n; i++) {
            tree[i].init(m);
        }
    }

    void update(int i, int j, int v) {
        for (int x = i; x < size; x = x | (x + 1))
            tree[x].add(j, v);
    }

    int get(int i, int j1, int j2) {
        int res = 0;
        for (int x = i; x >= 0; x = (x & (x + 1)) - 1)
            res += tree[x].calc(j1, j2 + 1);
        return res;
    }
    int get(int i1, int i2, int j1, int j2) {
        if (i1 > i2)
            return 0;
        return get(i2, j1, j2) - get(i1 - 1, j1, j2);
    }
};

struct Event {
    int x;
    int y, v;
    int time;
};
bool operator < (const Event& a, const Event& b)
{
    return a.x < b.x;
}

struct Query {
    int x;
    int y1, y2;
    int time;
};
bool operator < (const Query& a, const Query& b)
{
    return a.x < b.x;
}

int n, k;
pi prv;
ll ans = 0;
BITree segments;
vector<Query> queries;
vector<Event> events;
vector<int> xcords;
vector<int> ycords;

void make_update(const Event& a)
{
    segments.update(a.time, a.y, a.v);
}
void make_query(const Query& a)
{
    ans += segments.get(0, a.time - k, a.y1, a.y2);
    ans += segments.get(a.time + k, n, a.y1, a.y2);
}

int main(void)
{
    freopen("mowing.in", "r", stdin);
    freopen("mowing.out", "w", stdout);

    scanf("%d %d", &n, &k);

    scanf("%d %d", &prv.f, &prv.s);
    xcords.pb(prv.f);
    ycords.pb(prv.s);
    for (int i = 0; i < n - 1; i++) {
        pi cur;
        scanf("%d %d", &cur.f, &cur.s);

        if (cur.f == prv.f) {
            // same x => vertical segment => query
            Query new_quer;
            xcords.pb(new_quer.x = cur.f);
            new_quer.time = i;
            ycords.pb(new_quer.y1 = min(cur.s, prv.s) + 1);
            ycords.pb(new_quer.y2 = max(cur.s, prv.s) - 1);

            queries.push_back(new_quer);
        }
        else {
            // Same y => horizontal segment => event
            Event new_event;
            ycords.pb(new_event.y = cur.s);
            new_event.time = i;

            // Insertion event
            xcords.pb(new_event.x = min(prv.f, cur.f) + 1);
            new_event.v = 1;
            events.push_back(new_event);

            // Deletion event
            xcords.pb(new_event.x = max(prv.f, cur.f));
            new_event.v = -1;
            events.push_back(new_event);
        }

        prv = cur;
    }
    sort(events.begin(), events.end());
    sort(queries.begin(), queries.end());

    // Make compression
    sort(xcords.begin(), xcords.end());
    sort(ycords.begin(), ycords.end());
    xcords.resize(unique(xcords.begin(), xcords.end()) - xcords.begin());
    ycords.resize(unique(ycords.begin(), ycords.end()) - ycords.begin());

    for (auto& ev : events) {
        ev.x = lower_bound(xcords.begin(), xcords.end(), ev.x) - xcords.begin();
        ev.y = lower_bound(ycords.begin(), ycords.end(), ev.y) - ycords.begin();
    }
    for (auto& quer : queries) {
        quer.x = lower_bound(xcords.begin(), xcords.end(), quer.x) - xcords.begin();
        quer.y1 = lower_bound(ycords.begin(), ycords.end(), quer.y1) - ycords.begin();
        quer.y2 = lower_bound(ycords.begin(), ycords.end(), quer.y2) - ycords.begin();
    }

    segments.init(n + 1, ycords.size() + 1);

    int to_add = 0;
    for (auto vert : queries) {
        // Process the updates first
        while (to_add < events.size() && events[to_add].x <= vert.x) {
            make_update(events[to_add]);
            to_add++;
        }

        make_query(vert);

        // cerr << "QUERY NUMBER: " << i++ << endl;
    }

    printf("%lld\n", ans);

    return 0;
}