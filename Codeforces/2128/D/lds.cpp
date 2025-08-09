#include <bits/stdc++.h>

using namespace  std;

typedef long long ll;

int N;
vector<int> p;

void solve(void) {
    scanf("%d", &N);

    p.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &p[i]);
    }

    ll ans = 0;
    for (int len = 1; len <= N; len++) {
        ans = ans + (ll)len * (N - len + 1);
    }

    for (int i = 0; i < N - 1; i++) {
        if (p[i] < p[i + 1]) {
            ans = ans - (ll)(i + 1) * (N - i - 1);
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

    return 0;
}