#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, Q;
vector<int> a;

// tot[i]: Number of queries in which position i is used
vector<int> tot;

int main(void)
{
    scanf("%d %d", &N, &Q);

    a.resize(N);
    tot.resize(N + 1);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    sort(a.rbegin(), a.rend());

    for (int q = 0; q < Q; q++) {
        int l, r;
        scanf("%d %d", &l, &r);
        tot[l - 1]++;
        tot[r]--;
    }
    for (int i = 1; i <= N; i++) {
        tot[i] = tot[i] + tot[i - 1];
    }
    sort(tot.rbegin(), tot.rend());

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        ans += (ll)a[i] * tot[i];
    }

    printf("%lld\n", ans);

    return 0;
}