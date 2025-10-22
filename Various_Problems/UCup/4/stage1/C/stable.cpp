#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int H, W, S;

ll find_area(int ch, int cw) {
    if (cw < 0) {
        return INT_MAX;
    }
    cw = min(cw, W - 1);
    int hor = (H + ch) / (ch + 1);
    int ver = (W + cw) / (cw + 1);

    return (ll)hor * ver;
}

int test(int x) {
    int p = 1;
    int v = H;

    ll ans = find_area(p - 1, x - p - 1);

    while (p < H) {
        // Find value of p for which v changes
        int new_p = (H + v - 1) / v;
    }
}

void solve(void) {
    scanf("%d %d %d", &H, &W, &S);

    int l = -1;
    int r = H + W - 2;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (test(mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    printf("%d\n", r);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}