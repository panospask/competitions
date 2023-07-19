#include <bits/stdc++.h>

using namespace std;

const int QUERY = 1;
const int STUDENT = 0;

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
        int a = get(r - 1);
        int b = get(l - 1);

        return a - b;
    }
    int rget(int i) {
        return get(i, size);
    }
};

struct Event {
    int type;
    int x, y;
    int z;
    int id;
};
bool sumsort(const Event& a, const Event& b)
{
    if (a.z == b.z)
        return a.type < b.type;
    return a.z > b.z;
}
bool xsort(const Event& a, const Event& b)
{
    return a.x > b.x;
}

BITree b;
int N, Q;
vector<int> ycords;
vector<int> ans;
vector<Event> initial;

int find(int v)
{
    return lower_bound(ycords.begin(), ycords.end(), v) - ycords.begin();
}

void add_student(const Event& s, int mul = 1)
{
    if (s.type == QUERY)
        return;

    b.add(find(s.y), 1 * mul);
}
void make_query(const Event& s)
{
    if (s.type == STUDENT)
        return;

    ans[s.id] += b.rget(find(s.y));
}

void cdq_dc(vector<Event>& events)
{
    if (events.size() == 1) {
        // Nothing can be done
        return;
    }

    int mid = events.size() / 2;
    vector<Event> e1(mid), e2(events.size() - mid);

    for (int i = 0; i < mid; i++)
        e1[i] = events[i];
    for (int i = mid; i < events.size(); i++)
        e2[i - mid] = events[i];

    cdq_dc(e1);
    cdq_dc(e2);

    sort(e1.begin(), e1.end(), xsort);
    sort(e2.begin(), e2.end(), xsort);

    int to_add = 0;
    for (auto e : e2) {
        while (to_add < e1.size() && e1[to_add].x >= e.x) {
            add_student(e1[to_add]);
            to_add++;
        }

        make_query(e);
    }

    while (to_add) {
        to_add--;
        add_student(e1[to_add], -1);
    }
}

int main(void)
{
    scanf("%d %d", &N, &Q);

    ans.resize(Q);

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        ycords.push_back(y);

        initial.push_back({STUDENT, x, y, x + y, -1});
    }
    for (int i = 0; i < Q; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        ycords.push_back(y);

        initial.push_back({QUERY, x, y, z, i});
    }
    sort(initial.begin(), initial.end(), sumsort);
    sort(ycords.begin(), ycords.end());
    ycords.resize(unique(ycords.begin(), ycords.end()) - ycords.begin());

    b.init(ycords.size());
    cdq_dc(initial);

    for (int i = 0; i < Q; i++)
        printf("%d\n", ans[i]);

    return 0;
}