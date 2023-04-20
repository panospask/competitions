#include <bits/stdc++.h>

using namespace std;

struct segment
{
    long long int l, r;

    long long int size(void)
    {
        return r - l + 1;
    }
};
typedef struct segment Segment;

int n, k;
vector<Segment> segs;

bool operator < (Segment& a, Segment& b)
{
    if (a.size() == b.size())
        return a.l > b.l;
    return a.size() < b.size();
}

vector<Segment> seg_passed;
vector<Segment> actual;
void solve(void)
{
    scanf("%d %d", &n, &k);

    segs.resize(n);
    for (int i = 0; i < n; i++) 
        scanf("%lld", &segs[i].l);
    for (int i = 0; i < n; i++)
        scanf("%lld", &segs[i].r);

    // Do some merging
    actual.push_back(segs[0]);
    for (int i = 1; i < n; i++) {
        if (segs[i].l == actual.back().r + 1) {
            actual[actual.size() - 1].r = segs[i].r;
        }
        else 
            actual.push_back(segs[i]);
    }

    long long int total_squares = 0;
    int singlesegs = 0;
    int latest = 0;
    int rightmost = 0;
    long long int act_value = 0;
    for (int i = 0; i < actual.size() && total_squares < k; i++) {
        latest = i;
        total_squares += actual[i].size();
        rightmost = actual[i].r;
        if (actual[i].size() == 1)
            singlesegs++;
        act_value += 2;
    }

    if (total_squares < k) {
        printf("%d\n",-1);
        actual.clear();
        segs.clear();
        return;
    }

    // Check if removing the singlesegs is worth it
    int can_add = total_squares - k; // For the latest
    if (can_add) {
        int add = min(singlesegs, can_add);
        rightmost += add;
        singlesegs -= add;
        act_value -= add * 2;
    }
    act_value += rightmost;

    for (int i = latest + 1; i < actual.size(); i++) {
        int can_add = min(actual[i].size(), (long long)singlesegs);
        if (can_add) {
            int v = abs(actual[i].l + can_add - 1 - rightmost) + 2;
            int v2 = can_add * 2;
            if (v < v2) {
                act_value -= v2;
                act_value += abs(actual[i].l + can_add - 1 - rightmost) + 2;
                rightmost = actual[i].l + can_add - 1;
                singlesegs -= can_add;
            }
        }
    }

    printf("%lld\n", act_value);
    actual.clear();
    segs.clear();
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();

    return 0;
}