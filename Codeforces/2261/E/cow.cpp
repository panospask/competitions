#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> rbs;

// Segments of good brackets
vector<int> segments;
// Gaps between segments
vector<int> gaps;

// Prefix of gaps and segments
vector<int> pref;

void solve(void) {
    scanf("%d %d", &N, &K);

    rbs.resize(N);
    segments.clear();
    gaps.clear();
    int started = 0;
    for (int i = 0; i < N; i++) {
        char c;
        scanf(" %c", &c);

        if (c == '(') {
            rbs[i] = 1;
        }
        else {
            rbs[i] = 0;
        }

        if (rbs[i]) {
            if (started == 0) {
                segments.push_back(0);
                gaps.push_back(0);
                started = 1;
            }
            segments.back()++;
        }
        else {
            gaps.back()++;
            started = 0;
        }
    }

    int M = segments.size();
    pref.resize(M + 1);
    pref[0] = 0;
    for (int i = 0; i < M; i++) {
        pref[i + 1] = segments[i];
        if (i) {
            pref[i + 1] -= gaps[i - 1];
        }
        pref[i + 1] += pref[i];
    }
    
    int ans = 0;

    int cur = segments[0];
    int used = 0;
    // Which is the next target segment
    int r = 1;

    multiset<int> avail;
    avail.insert(pref[1]);

    for (int l = 0; l < M; l++) {
        while (used <= K && r < M) {
            if (gaps[r - 1] + used <= K) {
                used += gaps[r - 1];
                avail.insert(pref[r + 1]);
                r++;
            }
            else {
                break;
            }
        }

        int opt = *avail.rbegin();

        int res = opt - (pref[l]);
        if (l) {
            res += gaps[l - 1];
        }
        if (l == 0) {
            res = min(res + K, N / 2);
        }
        ans = max(ans, res);

        // Remove current option
        avail.erase(avail.find(pref[l + 1]));
        used -= gaps[l];
    }
    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}