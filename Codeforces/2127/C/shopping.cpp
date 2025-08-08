#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int N, K;
vector<int> a, b;
set<pi> values;

void solve(void) {
    scanf("%d %d", &N, &K);
    a.resize(N);
    b.resize(N);
    values.clear();

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }
    
    ll ans = 0;
    int add = INT_MAX;
    vector<int> big(N);
    vector<int> small(N);
    for (int i = 0; i < N; i++) {
        big[i] = max(a[i], b[i]);
        small[i] = min(a[i], b[i]);

        ans += big[i] - small[i];

        pi cur = mp(big[i], small[i]);
        auto it = values.lower_bound(cur);
        if (it != values.end()) {
            add = min(add, (*it).second - cur.first);
        }
        if (it != values.begin()) {
            it--;
            add = min(add, cur.second - (*it).first);
        }
        values.insert(cur);
    }
    add = max(add, 0);

    printf("%lld\n", ans + 2 * add);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}