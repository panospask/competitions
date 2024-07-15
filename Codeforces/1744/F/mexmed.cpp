#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> p;
// q[p[i]] = i
vector<int> q;
vector<bool> found;
int MEX = 0;

// We are in the segment [l..r]
int l, r = 0;

void move_to_next(void)
{
    if (MEX == 0) {
        l = r = q[0];
        found[0] = true;
        MEX++;
        return;
    }

    if (q[MEX] < l) {
        while (l > q[MEX]) {
            l--;
            found[p[l]] = true;
        }
    }
    else {
        while (r < q[MEX]) {
            r++;
            found[p[r]] = true;
        }
    }

    while (MEX < N && found[MEX]) {
        MEX++;
    }
}

void solve(void)
{
    scanf("%d", &N);

    MEX = 0;
    p.resize(N);
    q.resize(N + 1);
    q[N] = -1;
    found.assign(N, false);

    for (int i = 0; i < N; i++) {
        scanf("%d", &p[i]);
        q[p[i]] = i;
    }

    long long ans = 0;
    while (MEX < N) {
        move_to_next();

        int lmax, rmax;
        if (q[MEX] < l) {
            lmax = q[MEX] + 1;
            rmax = N - 1;
        }
        else {
            lmax = 0;
            rmax = q[MEX] - 1;
        }

        int maxlen = 2 * (MEX - 1) + 2;

        // Count all segments with lpoint in [lmax..l] and rpoint in [rmax..r] that have length <= maxlen

        if (q[MEX] < l) {
            for (int lpoint = max(lmax, r - maxlen + 1); lpoint <= l; lpoint++) {
                int R = min(lpoint + maxlen - 1, rmax);

                ans += R - r + 1;
            }
        }
        else {
            for (int rpoint = r; rpoint <= min(rmax, l + maxlen - 1); rpoint++) {
                int L = max(lmax, rpoint - maxlen + 1);

                ans += l - L + 1;
            }
        }
    }

    printf("%lld\n", ans);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}