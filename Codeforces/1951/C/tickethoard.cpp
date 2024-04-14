#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int N, M;
ll K;
vector<pi> a;

void solve(void)
{
    scanf("%d %d", &N, &M);
    scanf("%lld", &K);

    a.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i].first);
        a[i].second = i;
    }

    sort(a.begin(), a.end());

    ll cost = 0;
    int ttl_pos = 0;
    int i = 0;
    ll cur = K;
    __uint128_t remove = 0;
    while (cur > 0) {
        int price = a[i].first;
        ttl_pos++;

        int tickets = min(cur, (ll)M);
        cost += (ll)tickets * price;
        cur -= tickets;
        remove += (ll)tickets * tickets;
        i++;
    }
    cost += ((__uint128_t)K * K - remove) / 2;

    printf("%lld\n", cost);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}