#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

typedef long long ll;

int N;
vector<pi> l, r;
vector<pi> segment;

ll test(int x) {
    if (x >= N) {
        return 0;
    }
    multiset<int> best_right;
    multiset<int> best_left;
    priority_queue<int> lcheck, rcheck;
    multiset<pi> diff;
    for (int i = 0; i < N; i++) {
        if (segment[i].first <= x) {
            if (segment[i].second >= x) {
                // We WILL consider removing from best left and pushing to best right if need be
                diff.insert({segment[i].second + segment[i].first - 2 * x, i});
            }
            else {
                best_left.insert(-segment[i].first);
            }
        }
        else if (segment[i].second >= x) {
            best_right.insert(segment[i].second);
        }
    }

    while (best_right.size() >= N / 2) {
        best_right.erase(best_right.begin());
    }
    while (best_left.size() >= N / 2) {
        best_left.erase(best_left.begin());
    }

    while (best_right.size() < N / 2 && !diff.empty()) {
        int idx = (*prev(diff.end())).second;
        diff.erase(prev(diff.end()));
        best_right.insert(segment[idx].second);
    }
    while (best_right.size() < N / 2 && !diff.empty()) {
        int idx = (*diff.begin()).second;
        diff.erase(diff.begin());
        best_right.insert(segment[idx].second);
    }
    if (best_left.size() < N / 2 || best_right.size() < N / 2) {
        return 0;
    }

    while (!diff.empty()) {
        int idx = (*diff.begin()).second;
        diff.erase(diff.begin());

        int v = segment[idx].second + segment[idx].first - 2 * x;
        if (segment[idx].second - *best_right.begin() <= -segment[idx].first - *best_left.begin()) {
            if (-segment[idx].first - *best_left.begin() > 0) {
                best_left.erase(best_left.begin());
                best_left.insert(-segment[idx].first);
            }
        }
        else if (segment[idx].second - *best_right.begin() > 0) {
            best_right.erase(best_right.begin());
            best_right.insert(segment[idx].second);
        }
    }

    ll res = 0;
    while (best_right.size()) {
        res += *best_right.begin();
        best_right.erase(best_right.begin());
    }
    while (best_left.size()) {
        res += *best_left.begin();
        best_left.erase(best_left.begin());
    }
    return res;
}

void solve(void) {
    scanf("%d", &N);

    l.resize(N);
    r.resize(N);
    segment.resize(N);

    ll ans = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &segment[i].first, &segment[i].second);
        l[i] = {segment[i].first, i};
        r[i] = {segment[i].second, i};

        ans += segment[i].second - segment[i].first;
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    int l = 0;
    int r = N - 1;
    while (l + 2 < r) {
        int m1 = (l + l + r) / 3;
        int m2 = (l + r + r) / 3;

        ll v1 = test(m1);
        ll v2 = test(m2);
        if (v1 > v2) {
            r = m2;
        }
        else if (v2 > v1) {
            l = m1;
        }
        else {
            l = m1;
            r = m2;
        }
    }

    printf("%lld\n", max(test(l), max(test(l + 1), test(l + 2))) + ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}