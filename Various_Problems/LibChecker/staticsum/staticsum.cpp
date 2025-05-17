#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, Q;
vector<ll> pref;
vector<int> a;

int main(void) {
    scanf("%d %d", &N, &Q);

    pref.resize(N + 1);
    a.resize(N + 1);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);
    }
    pref[0] = 0;
    for (int i = 0; i < N; i++) {
        pref[i + 1] = pref[i] + a[i + 1];
    }

    for (int i = 0; i < Q; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        l++;

        printf("%lld\n", pref[r] - pref[l - 1]);
    }

    return 0;
}