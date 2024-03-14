#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const int UPDATE = 0;
const int QUERY = 1;

struct Point {
    int type;
    int id;
    int position;
    bool l;
};

int N, Q;
vector<Point> points;
vector<int> updates;
vector<ll> ans;

bool pointcomp(const Point& a, const Point& b)
{
    return a.position < b.position;
}

int main(void)
{
    scanf("%d %d", &N, &Q);

    updates.resize(N);
    ans.assign(Q, 0);

    for (int i = 0; i < N; i++) {
        int l, r, v;
        scanf("%d %d %d", &l, &r, &v);
        updates[i] = v;
        points.pb({UPDATE, i, l, true});
        points.pb({UPDATE, i, r, false});
    }
    for (int i = 0; i < Q; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        points.pb({QUERY, i, l, true});
        points.pb({QUERY, i, r, false});
    }

    sort(points.begin(), points.end(), pointcomp);

    ll cur_sum = 0;
    ll cur_add = 0;
    ll pos = 0;
    for (int i = 0; i < points.size(); i++) {
        Point cur = points[i];

        cur_sum += (cur.position - pos) * cur_add;
        pos = cur.position;

        if (cur.type == QUERY) {
            if (cur.l) {
                ans[cur.id] -= cur_sum;
            }
            else {
                ans[cur.id] += cur_sum;
            }
        }
        else {
            if (cur.l) {
                cur_add += updates[cur.id];
            }
            else {
                cur_add -= updates[cur.id];
            }
        }
    }

    for (int i = 0; i < Q; i++)
        printf("%lld\n", ans[i]);

    return 0;
}