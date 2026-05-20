#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

const int INF = 2e6;

int N;
vector<int> exist;
vector<vector<pi>> points;

void solve(void) {
    scanf("%d", &N);

    exist.assign(N, 0);
    points.assign(N + 1, vector<pi>());
    for (int i = 0; i < N; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        b--;
        points[a].push_back({a, b});
        exist[b]++;
    }

    // Extract 
    vector<int> y;
    for (int i = 0; i < N; i++) {
        if (exist[i]) {
            y.push_back(i);
        }
    }

    int p = 0;

    vector<int> lmin(N + 1);
    vector<int> lmax(N + 1);
    vector<int> rmin(N + 1);
    vector<int> rmax(N + 1);
    lmin[0] = y.size() - 1;
    lmax[0] = 0;

    for (int i = 1; i <= N; i++) {
        lmin[i] = lmin[i - 1];
        lmax[i] = lmax[i - 1];
        for (auto p : points[i]) {
            // Move everything in i from r to l
            while (p.second < y[lmin[i]]) {
                lmin[i]--;
            }
            while (p.second > y[lmax[i]]) {
                lmax[i]++;
            }
        }
    }

    rmax[N] = 0;
    rmin[N] = y.size() - 1;
    for (int i = N - 1; i >= 0; i--) {
        rmin[i] = rmin[i + 1];
        rmax[i] = rmax[i + 1];
        for (auto p : points[i + 1]) {
            // Move everything in i + 1 from l to r
            while (p.second < y[rmin[i]]) {
                rmin[i]--;
            }
            while (p.second > y[rmax[i]]) {
                rmax[i]++;
            }
        }
    }

    long long ans = 0;

    int left = 0;
    for (int i = 0; i < N; i++) {
        if (points[i].size() == 0) {
            continue;
        }
        left += points[i].size();
        if (left != 0 && left != N) {
            int mn = max(lmin[i], rmin[i]);
            int mx = min(lmax[i], rmax[i]);

            if (mn > mx) {
                continue;
            }

            ans += mx - mn;
        }
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}