#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

int N, Q;
vector<pi> ranges;
int cnt = 0;

bool rangesort(pi a, pi b) {
    if (a.first == b.first) {
        return a.second > b.second;
    }

    return a.first < b.first;
}

int query(int l, int r) {
    printf("? %d %d\n", l + 1, r + 1);
    fflush(stdout);

    int res;
    scanf("%d", &res);
    return res;
}
int query(pi r) {
    return query(r.first, r.second);
}

pi make(vector<pi>& ranges, int l, int r) {
    return make_pair(ranges[l].first, ranges[r - 1].second);
}

void solve(void) {
    scanf("%d %d", &N, &Q);

    ranges.resize(Q);
    for (int i = 0; i < Q; i++) {
        scanf("%d %d", &ranges[i].first, &ranges[i].second);
        ranges[i].first--;
        ranges[i].second--;
    }
    sort(ranges.begin(), ranges.end(), rangesort);

    // // Calculate index of 0
    // int l = -1;
    // int r = N - 1;
    // while (l + 1 < r) {
    //     int mid = (l + r) / 2;
    //     if (query(0, mid) > 0) {
    //         r = mid;
    //     }
    //     else {
    //         l = mid;
    //     }
    // }

    // int idx = r;

    // Purge some ranges
    vector<pi> goodranges;
    int prv_r = -1;
    for (int i = 0; i < Q; i++) {
        if (ranges[i].second > prv_r) {
            goodranges.pb(ranges[i]);
            prv_r = ranges[i].second;
        }
    }

    if (goodranges.size() == 0) {
        printf("! 0\n");
        fflush(stdout);
        return;
    }

    // Binary search on them
    int l = 0;
    int r = goodranges.size();
    int ans = 0;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        int ans1 = query(make(goodranges, l, mid));
        int ans2 = query(make(goodranges, mid, r));
        if (ans1 > ans2) {
            r = mid;
        }
        else {
            l = mid;
        }
    }
    ans = query(goodranges[l]);

    printf("! %d\n", ans);
    fflush(stdout);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}