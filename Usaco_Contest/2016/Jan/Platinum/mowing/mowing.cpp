#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

struct BITree {
    int size;
    vector<int> tree;

    void init(int n) {
        size = n;
        tree.assign(size, 0);
    }

    void add(int i, int v) {
        for (int x = i; x < size; x = x | (x + 1))
            tree[x] += v;
    }
    int get(int i) {
        int res = 0;
        for (int x = i; x >= 0; x = (x & (x + 1)) - 1)
            res += tree[x];
        return res;
    }
    int get(int l, int r) {
        return get(r) - get(l - 1);
    }
};

struct Query {
    // updateval is 0 iff it is a query, not an update
    int updateval = 0;

    int t;
    int x;
    // y1 < y2
    int y1, y2;
};
bool timesort(const Query& a, const Query& b)
{
    return a.t < b.t;
}
bool possort(const Query& a, const Query& b)
{
    if (a.x == b.x)
        return a.updateval > b.updateval;
    return a.x < b.x;
}

int n, k;
vector<pair<int, int>> points;
vector<Query> initial;
vector<int> xcords;
vector<int> ycords;
ll ans = 0;
BITree st;

void update_with(const Query& a, int mul = 1)
{
    if (a.updateval == 0)
        return;

    st.add(a.y1, a.updateval * mul);
}
void query_with(const Query& a)
{
    if (a.updateval != 0)
        return;

    int pans = ans;
    ans += st.get(a.y1, a.y2);

}

void calculate(vector<Query>& queries)
{
    if (queries.size() == 1) {
        // Nothing to be done
        return;
    }

    int mid = queries.size() / 2;
    vector<Query> q1(mid), q2(queries.size() - mid);
    for (int i = 0; i < mid; i++)
        q1[i] = queries[i];
    for (int i = mid; i < queries.size(); i++)
        q2[i - mid] = queries[i];

    calculate(q1);
    calculate(q2);

    sort(q1.begin(), q1.end(), timesort);
    sort(q2.begin(), q2.end(), timesort);

    int to_add = 0;
    for (auto quer : q2) {
        while (to_add < mid && q1[to_add].t + k <= quer.t) {
            update_with(q1[to_add]);
            to_add++;
        }

        query_with(quer);
    }
    while (to_add) {
        update_with(q1[to_add - 1], -1);
        to_add--;
    }

    reverse(q1.begin(), q1.end());
    reverse(q2.begin(), q2.end());

    for (auto quer : q2) {
        while (to_add < mid && q1[to_add].t >= quer.t + k) {
            update_with(q1[to_add]);
            to_add++;
        }

        query_with(quer);
    }
    while (to_add) {
        update_with(q1[to_add - 1], -1);
        to_add--;
    }

    return;
}

int compress(int x, bool y)
{
    if (y)
        return lower_bound(ycords.begin(), ycords.end(), x) - ycords.begin();
    else
        return lower_bound(xcords.begin(), xcords.end(), x) - xcords.begin();
}

int main(void)
{
    freopen("mowing.in", "r", stdin);
    freopen("mowing.out", "w", stdout);

    scanf("%d %d", &n, &k);
    points.resize(n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].first, &points[i].second);
        xcords.push_back(points[i].first);
        ycords.push_back(points[i].second);
    }
    sort(xcords.begin(), xcords.end());
    sort(ycords.begin(), ycords.end());
    xcords.resize(unique(xcords.begin(), xcords.end()) - xcords.begin());
    ycords.resize(unique(ycords.begin(), ycords.end()) - ycords.begin());
    st.init(ycords.size());

    for (int i = 0; i + 1 < n; i++) {
        pair<int, int> p0 = points[i];
        p0.first = compress(p0.first, 0);
        p0.second = compress(p0.second, 1);
        pair<int, int> p1 = points[i + 1];
        p1.first = compress(p1.first, 0);
        p1.second = compress(p1.second, 1);

        Query cur;
        cur.t = i;
        if (p0.first == p1.first) {
            // It's a y segment
            cur.updateval = 0;
            cur.x = p0.first;
            cur.y1 = p0.second;
            cur.y2 = p1.second;
            if (cur.y1 > cur.y2)
                swap(cur.y1, cur.y2);
            cur.y1++;
            cur.y2--;

            initial.push_back(cur);
        }
        else {
            if (p0.first > p1.first)
                swap(p0.first, p1.first);

            // It's an x segment
            cur.updateval = 1;
            cur.x = p0.first + 1;
            cur.y1 = p0.second;
            initial.push_back(cur);
            cur.updateval = -1;
            cur.x = p1.first - 1;
            initial.push_back(cur);
        }
    }

    sort(initial.begin(), initial.end(), possort);

    calculate(initial);

    printf("%lld\n", ans);

    return 0;
}