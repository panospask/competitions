#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, q;
vector<ll> pref;
vector<int> a;

int main(void)
{
    scanf("%d %d", &n, &q);

    a.resize(n + 1);
    pref.resize(n + 1);
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        pref[i] = pref[i - 1] + a[i];
    }

    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);

        printf("%lld\n", pref[b] - pref[a - 1]);
    }

    return 0;
}