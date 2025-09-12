#include <bits/stdc++.h>

using namespace std;


typedef long long ll;
const ll INF = 1e18;

int N;
vector<int> a;

int sign(int p) {
    if (p == 0) {
        return 1;
    }
    else {
        return -1;
    }
}

ll calculate_cost(void) {
    ll res = 0;
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            res += a[i];
        }
        else {
            res -= a[i];
        }
    }
    return res;
}

void solve(void) {
    scanf("%d", &N);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    // Even to odd and odd to even
    ll change[2] = {-INF, -INF};
    ll ans = 0;
    ll v = calculate_cost();
    for (int i = 0; i < N; i++) {
        int p = i % 2;

        ans = max(ans, change[!p] + i - (ll)2 * sign(p) * a[i]);

        change[p] = max(change[p], -i - (ll)2 * sign(p) * a[i]);
    }
    ans = max(ans, (ll)2 * ((N - 1) / 2));
    printf("%lld\n", ans + v);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}