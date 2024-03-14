#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M, Q;

ll C;
vector<int> a, b;
vector<ll> pref;
set<ll> v;

ll calculate(void)
{
    ll ans = LLONG_MAX;
    auto it = v.lower_bound(C);

    if (it != v.end()) {
        ans = min(ans, abs(C - *it));
    }
    if (it != v.begin()) {
        it--;
        ans = min(ans, abs(C - *it));
    }

    return ans;
}

void update(int l, int r, int x)
{
    // Updates the value C

    if (l % 2 && r % 2) {
        C += x;
    }
    if (!(l % 2) && !(r % 2)) {
        C -= x;
    }
}

int sign(int i)
{
    if (i % 2)
        return 1;
    else
        return -1;
}

int main(void)
{
    scanf("%d %d %d", &N, &M, &Q);

    a.resize(N + 1);
    b.resize(M + 1);
    pref.assign(M + 1, 0);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);
        C += a[i] * sign(i);
    }
    for (int j = 1; j <= M; j++) {
        scanf("%d", &b[j]);
        pref[j] = pref[j - 1] + b[j] * sign(j);
    }
    for (int j = 0; j <= M - N; j++) {
        v.insert((pref[j + N] - pref[j]) * sign(j+1));
    }

    printf("%lld\n", calculate());
    for (int i = 0; i < Q; i++) {
        int l, r, x;
        scanf("%d %d %d", &l, &r, &x);

        update(l, r, x);
        printf("%lld\n", calculate());
    }

    return 0;
}