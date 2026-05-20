#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int P, Q;
int total;

bool test(int n, int m) {
    if (P >= m - n) {
        return true;
    }
    return false;
}

int find(int i) {
    int l = -1;
    int r = total;

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if ((ll)2 * i * mid + i + mid <= total) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    if ((ll)2 * l * i + i + l == total) {
        return l;
    }
    else {
        return 0;
    }
}

void solve(void) {
    scanf("%d %d", &P, &Q);
    total = P + 2 * Q;

    int n = -1, m;
    for (int i = 1; i * i < total; i++) {
        int r = find(i);
        if (r && r < i) {
            break;
        }
        if (r) {
            if (test(i, r)) {
                n = i;
                m = r;
            }
        }
    }

    if (n == -1) {
        printf("-1\n");
    }
    else {
        printf("%d %d\n", n, m);
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}