#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<ll> d;

void solve(void)
{
    scanf("%d", &N);

    d.resize(2 * N);
    bool good = true;
    for (int i = 0; i < 2 * N; i++) {
        scanf("%lld", &d[i]);

        if (d[i] % 2) {
            good = false;
        }
        d[i] /= 2;
    }
    if (!good) {
        printf("NO\n");
        return;
    }
    sort(d.rbegin(), d.rend());

    ll s = 0;
    ll prv = LLONG_MAX;
    int rem = N;
    for (int i = 0; i < 2 * N; i += 2) {
        if (d[i] != d[i + 1]) {
            printf("NO\n");
            return;
        }

        if ((d[i] - s) % rem) {
            printf("NO\n");
            return;
        }

        ll ele = (d[i] - s) / rem;
        if (ele <= 0 || ele >= prv) {
            printf("NO\n");
            return;
        }

        s += ele;
        prv = ele;
        rem--;
    }

    printf("YES\n");
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