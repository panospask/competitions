#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N, K;
// When is each member available
multiset<int> available;
vector<pi> movies;

int main(void) {
    scanf("%d %d", &N, &K);

    movies.resize(N);
    for (int i = 0; i < N; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        movies[i] = make_pair(b, a);
    }
    sort(movies.begin(), movies.end());

    for (int i = 0; i < K; i++) {
        available.insert(0);
    }

    // We want v <= a
    // If we find first v s.t v > a
    int ans = 0;
    for (auto [b, a] : movies) {
        auto nxt = available.upper_bound(a);
        if (nxt == available.begin()) {
            continue;
        }

        int t = *prev(nxt);
        ans++;
        available.erase(available.find(t));
        available.insert(b);
    }

    printf("%d\n", ans);

    return 0;
}