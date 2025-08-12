#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> H, C;

ll cost(int x) {
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        ans += abs(H[i] - x) * (ll)C[i];
    }

    return ans;
}

void solve(void) {
    scanf("%d", &N);

    H.resize(N);
    C.resize(N);
    int maxH = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &H[i]);
        maxH = max(maxH, H[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }

    int l = -1;
    int r = maxH;
    while (l + 1 < r) {
        int mid = (l + r) / 2;

        // We want to check if function decreases or increases after mid
        if (cost(mid) > cost(mid + 1)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    printf("%lld\n", cost(r));
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}