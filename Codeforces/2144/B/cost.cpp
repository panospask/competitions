#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> p;
vector<bool> missing;

void solve(void) {
    scanf("%d", &N);

    p.resize(N);
    missing.assign(N, true);

    int l = N;
    int r = 0;
    int rem = N;
    for (int i = 0; i < N; i++) {
        scanf("%d", &p[i]);
        p[i]--;
        if (p[i] != -1) {
            missing[p[i]] = false;
            rem--;
        }
        if (p[i] != i && p[i] != -1) {
            l = min(l, min(i, p[i]));
            r = max(r, max(i, p[i]));
        }
    }

    if (rem > 1) {
        // Find first and last missing
        for (int i = 0; i < N; i++) {
            if (missing[i]) {
                l = min(l, i);
                r = max(r, i);
            }
        }
    }

    int ans = max(r - l + 1, 0);
    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}