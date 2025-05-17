#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, K;
vector<int> many, few;

void solve(void) {
    scanf("%d %d", &N, &K);

    many.resize(N);
    few.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &many[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &few[i]);
        if (many[i] < few[i]) {
            swap(many[i], few[i]);
        }
    }

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        ans += many[i];
    }

    sort(few.rbegin(), few.rend());
    for (int i = 0; i < K - 1; i++) {
        ans += few[i];
    }
    ans++;

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}