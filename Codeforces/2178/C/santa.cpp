#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e17;

int N;
vector<int> A;

vector<ll> suff;

void solve(void) {
    scanf("%d", &N);
    
    A.resize(N);
    suff.resize(N + 1);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    suff[N] = 0;
    for (int i = N - 1; i >= 0; i--) {
        suff[i] = suff[i + 1] + A[i];
    }

    ll cur = 0;
    ll ans = -INF;
    for (int i = 0; i < N; i++) {
        // What if i is indifferent element
        ans = max(ans, cur - suff[i + 1]);

        if (i == 0) {
            cur += A[i];
        }
        else {
            cur += max(A[i], -A[i]);
        }
    }

    printf("%lld\n", ans);

    return;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}