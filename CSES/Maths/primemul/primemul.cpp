#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << pos))

using namespace std;

typedef long long ll;

ll N;
int K;
vector<ll> a;

int main(void)
{
    scanf("%lld %d", &N, &K);

    a.resize(K);
    for (int i = 0; i < K; i++) {
        scanf("%lld", &a[i]);
    }

    ll ans = 0;
    for (int s = 1; s < (1 << K); s++) {
        ll prod = 1;
        bool good = true;
        int setsize = __builtin_popcount(s);

        for (int i = 0; i < K; i++) {
            if (!CHECK_BIT(s, i)) {
                continue;
            }

            if (sqrt(prod) * sqrt(a[i]) > sqrt(N) + 5) {
                good = false;
                break;
            }

            prod *= a[i];
        }

        if (good) {
            ans += N / prod * (setsize % 2 ? 1 : -1);
        }
    }

    printf("%lld\n", ans);
}