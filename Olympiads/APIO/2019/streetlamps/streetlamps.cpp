#include <bits/stdc++.h>

using namespace std;

struct BITree {
    int size;
    vector<int> tree;

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

    void init(int n) {
        size = n;
        tree.assign(size, 0);
    }
};

const int POINT = 0;
const int START_Q = -1;
const int END_Q = 1;
struct Event {
    int type;
    int time;
    int x;
    int y;

    // Variables for points only
    int value;

    // Variables for queries only
    int id;
};
bool x_sort(const Event& a, const Event& b)
{
    return a.x < b.x;
}

struct LitUp {
    int l, r;
    int time_on;

    LitUp(int a, int b, int c) : l(a), r(b), time_on(c) {};
};
bool operator <(const LitUp& a, const LitUp& b)
{
    return a.l < b.l;
}

int n, q;
vector<int> ans;
BITree segments;
set<LitUp> active;
vector<bool> bulbs;
vector<Event> events;

void update(const Event& a, int mul = 1)
{
    if (a.type != POINT)
        return;
    segments.add(a.y, a.value * mul);
}
void query(const Event& a)
{
    if (a.type == POINT)
        return;

    ans[a.id] += a.type * segments.get(a.y, n);
}

void divide_and_conquer(vector<Event>& events)
{
    if (events.size() == 1)
        return;

    int mid = events.size() / 2;
    vector<Event> ev1(mid), ev2(events.size() - mid);
    for (int i = 0; i < mid; i++)
        ev1[i] = events[i];
    for (int i = mid; i < events.size(); i++)
        ev2[i - mid] = events[i];

    divide_and_conquer(ev1);
    divide_and_conquer(ev2);

    sort(ev1.begin(), ev1.end(), x_sort);
    sort(ev2.begin(), ev2.end(), x_sort);

    int to_add = 0;
    for (auto& e : ev2) {
        while (to_add < mid && ev1[to_add].x <= e.x) {
            update(ev1[to_add]);
            to_add++;
        }

        query(e);
    }
    while (to_add) {
        to_add--;
        update(ev1[to_add], -1);
    }
}

void make_events(void)
{
    char cur[10];
    for (int t = 1; t <= q; t++) {
        scanf("%s", cur);
        if (cur[0] == 't') {
            int i;
            scanf("%d", &i);
            i--;

            if (bulbs[i]) {
                // Seperate point i from point i + 1
                LitUp prv = *prev(active.upper_bound({i, 0, 0}));
                active.erase(prv);
                int v = t - prv.time_on;

                events.push_back({POINT, t, prv.l, prv.r, v, t});
                active.insert({prv.l, i, t});
                active.insert({i + 1, prv.r, t});
            }
            else {
                // Unite point i and point i + 1
                LitUp p1 = *prev(active.upper_bound({i, 0, 0}));
                LitUp p2 = *prev(active.upper_bound({i + 1, 0, 0}));
                active.erase(p1);
                active.erase(p2);

                events.push_back({POINT, t, p1.l, p1.r, t - p1.time_on, t});
                events.push_back({POINT, t, p2.l, p2.r, t - p2.time_on, t});

                active.insert({p1.l, p2.r, t});
            }

            bulbs[i] = !bulbs[i];
        }
        else {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;
            ans[t]++;

            // Check if the segment is active
            LitUp p1 = *prev(active.upper_bound({a, 0, 0}));
            LitUp p2 = *prev(active.upper_bound({b, 0, 0}));

            if (p1.l == p2.l) {
                ans[t] += t - p1.time_on;
            }

            // Create the query
            events.push_back({END_Q, t, a, b, -1, t});
        }
    }
}

void read_process_input(void)
{
    scanf("%d %d", &n, &q);

    ans.assign(q + 1, -1);
    segments.init(n + 1);
    bulbs.resize(n);

    int latest_point = 0;
    for (int i = 0; i < n; i++) {
        int cond;
        scanf("%1d", &cond);
        bulbs[i] = cond;

        if (!cond) {
            active.insert({latest_point, i, 0});
            latest_point = i + 1;
        }
    }
    active.insert({latest_point, n, 0});

    make_events();

    active.clear();
}

// #define DEBUG
int main(void)
{
    #ifdef DEBUG
        freopen("streetlamps.in", "r", stdin);
    #endif

    read_process_input();
    divide_and_conquer(events);

    for (int i = 1; i <= q; i++) {
        if (ans[i] != -1)
            printf("%d\n", ans[i]);
    }

    return 0;
}