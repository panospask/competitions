#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;

// Query [l, r)
ll query(int l, int r) {
    printf("? %d %d\n", l + 1, r);
    fflush(stdout);

    ll res;
    scanf("%lld", &res);

    return res;
}

// Return range [l, s) with target sum
int find(ll sum, int l, int r) {
    int l2 = l + 1;
    int r2 = r;

    while (l2 + 1 < r2) {
        int mid = (l2 + r2) / 2;
        if (query(l, mid) <= sum) {
            l2 = mid;
        }
        else {
            r2 = mid;
        }
    }

    return l2;
}

ll compute(int l, int r, ll s) {
    if (s % 2 == 1) {
        if (r - l == s) {
            return 1;
        }
        else {
            return 2;
        }
    }
    if (l == r - 1) {
        return query(l, l + 1);
    }

    int m = find(s / 2, l, r);
    if (m - l <= r - m) {
        return compute(l, m, s / 2);
    }
    else {
        return compute(m, r, s / 2);
    }
}

void solve(void) {
    scanf("%d", &N);

    ll sum = query(0, N);
    ll ans = compute(0, N, sum);

    printf("! %lld\n", ans);
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