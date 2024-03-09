#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> a;
multiset<int> chosen;

int main(void)
{
    scanf("%d", &N);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < N; i += 2) {
        int best = max(a[i], a[i + 1]);
        int worst = min(a[i], a[i + 1]);

        // Surely take this
        chosen.insert(best);

        // Sometimes also take the worst
        if (*chosen.begin() < worst) {
            chosen.erase(chosen.begin());
            chosen.insert(worst);
        }
    }

    ll ans = 0;
    while (chosen.size()) {
        ans += *chosen.begin();
        chosen.erase(chosen.begin());
    }

    printf("%lld\n", ans);
    return 0;
}