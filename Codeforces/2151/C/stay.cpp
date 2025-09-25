#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> A;

vector<ll> pref;

vector<ll> ans;

// Find sum [l, r)
ll find_sum(int l, int r) {
    return pref[r] - pref[l];
}

void solve(void) {
    scanf("%d", &N);

    A.resize(2 * N);
    pref.resize(2 * N + 1);
    pref[0] = 0;
    ans.resize(N + 1);

    for (int i = 0; i < 2 * N; i++) {
        scanf("%d", &A[i]);
        pref[i + 1] = pref[i] + A[i];        
    }
    
    ll pos = 0, neg = 0;
    ans[N] = find_sum(N, 2 * N) - find_sum(0, N);

    for (int i = N - 1; i >= 0; i--) {
        ll n_pos = neg + A[i];
        ll n_neg = pos + A[2 * N - i - 1];
        
        pos = n_pos;
        neg = n_neg;

        ans[i] = -find_sum(0, i) + n_pos - n_neg + find_sum(2 * N - i, 2 * N);
    }

    for (int i = 0; i < N; i++) {
        printf("%lld ", ans[i + 1]);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}