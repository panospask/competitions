#include <bits/stdc++.h>

using namespace std;

int main(void) {
    int X, N;
    vector<int> p;

    scanf("%d %d", &X, &N);
    p.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &p[i]);
    }

    // Positions of traffic lights
    set<int> l;
    multiset<int> d;

    // Initially, virtual (fake) traffic light in positions 0 and X
    l.insert(0);
    l.insert(X);

    d.insert(X - 0);

    for (int i = 0; i < N; i++) {
        // Place light at p[i]

        auto nxt = l.upper_bound(p[i]);
        auto prv = prev(nxt);

        int d_nxt = *nxt;
        int d_prv = *prv;

        int dist = d_nxt - d_prv;

        d.erase(d.find(dist));
        d.insert(d_nxt - p[i]);
        d.insert(p[i] - d_prv);

        l.insert(p[i]);

        int ans = *d.rbegin();
        printf("%d ", ans);
    }
    printf("\n");

    return 0;
}