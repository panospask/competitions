#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

struct segtree {

    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(size * 2, 0);
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
            add(i ,v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void add(int i, int v){
        add(i, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r)
            return 0;
        else if (l <= lx && rx <= r)
            return tree[x];

        int mid = (lx + rx) / 2;
        return calc(l, r, 2 * x + 1, lx, mid) + calc(l, r, 2 * x + 2, mid, rx);
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int n;
int total_x, total_y;
vector<pair<ii, int>> hor_segments;
vector<pair<int, ii>> ver_segments;
set<int> x;
set<int> y;
map<int, int> x_compress;
map<int, int> y_compress;
segtree st;
multiset<ii> y_remove_at;

bool compfunc(const pair<ii, int>& a, const pair<ii, int>& b)
{
    return a.second < b.second;
}

bool secondcomp(const pair<int, ii>& a, const pair<int, ii>& b)
{
    return a.second.first < b.second.first;
}

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if (x1 == x2)
            ver_segments.push_back(mp(x1, mp(y1, y2)));
        else
            hor_segments.push_back(mp(mp(x1, x2), y1));

        x.insert(x1);
        x.insert(x2);
        y.insert(y1);
        y.insert(y2);
    }

    // Compress coordinates
    total_x = x.size();
    int i = 0;
    for (auto c : x) {
        x_compress[c] = i++;
    }

    total_y = y.size();
    i = 0;
    for (auto c : y) {
        y_compress[c] = i++;
    }

    sort(hor_segments.begin(), hor_segments.end(), compfunc);
    sort(ver_segments.begin(), ver_segments.end(), secondcomp);

    st.init(total_x);
    int x_pointer = 0;
    int y_pointer = 0;
    long long ans =0;
    for (int i = 0; i < total_y; i++) {
        // Add the y segments
        while (y_pointer < ver_segments.size() && y_compress[ver_segments[y_pointer].second.first] < i)
            y_pointer++;

        while (y_pointer < ver_segments.size() && y_compress[ver_segments[y_pointer].second.first] == i) {
            st.add(x_compress[ver_segments[y_pointer].first], 1);
            y_remove_at.insert(mp(y_compress[ver_segments[y_pointer].second.second], x_compress[ver_segments[y_pointer].first]));
            y_pointer++;
        }

        // Add the x segments
        while (x_pointer < hor_segments.size() && y_compress[hor_segments[x_pointer].second] < i)
            x_pointer++;

        while (x_pointer < hor_segments.size() && y_compress[hor_segments[x_pointer].second] == i) {
            int v1 = x_compress[hor_segments[x_pointer].first.first];
            int v2 = x_compress[hor_segments[x_pointer].first.second];
            ans += st.calc(v1, v2 + 1);
            x_pointer++;
        }

        // Remove the y segments
        while (!y_remove_at.empty()) {
            auto seg = *(y_remove_at.begin());
            if (seg.first == i) {
                st.add(seg.second, -1);
                y_remove_at.erase(y_remove_at.begin());
            }
            else
                break;
        }
    }

    printf("%lld\n", ans);
}