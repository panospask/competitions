#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
ll K;
vector<int> a;

vector<int> forgot;
vector<int> forgotten;
vector<ll> pref;
vector<ll> suff;

void solve(void) {
    scanf("%d %lld", &N, &K);

    a.resize(N);
    pref.resize(N);
    suff.resize(N);
    forgot.resize(N);
    forgotten.clear();

    for (int i = 0; i < N; i++) {
        scanf("%1d", &forgot[i]);
        forgot[i] = !forgot[i];
        if (forgot[i]) {
            forgotten.push_back(i);
        }
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    pref[0] = max(a[0], 0);
    for (int i = 1; i < N; i++) {
        ll take = 0;
        if (!forgot[i - 1]) {
            take = pref[i - 1];
        }

        pref[i] = max(take + a[i], 0LL);
    }

    suff[N - 1] = max(a[N - 1], 0);
    for (int i = N - 2; i >= 0; i--) {
        ll take = 0;
        if (!forgot[i + 1]) {
            take = suff[i + 1];
        }

        suff[i] = max(take + a[i], 0LL);
    }

    ll best = 0;
    for (int i = 0; i < N; i++) {
        best = max(best, pref[i]);
    }

    if (best > K || (best != K && forgotten.empty())) {
        printf("No\n");
        return;
    }

    printf("Yes\n");
    for (int i = 0; i < N; i++) {
        if (!forgot[i]) {
            printf("%d ", a[i]);
        }
        else if (i == forgotten[0]) {
            printf("%lld ", K - pref[i] - suff[i]);
        }
        else {
            printf("%lld ", (ll)-1e18 + 1);
        }
    }
    printf("\n");

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