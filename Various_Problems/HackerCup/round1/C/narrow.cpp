#include <bits/stdc++.h>

#define CHECK_BIT(var, pos) (((var) & (1 << (pos))) == 0)

using namespace std;

typedef long long ll;
typedef pair<int, ll> pi;

const int BITS = 30;

struct Group {
    ll total_cost = 0;
    
    // Last number that has been made 0
    int last = 0;
    int cnt = 0;

    // Sum of (1 before every start)
    int sum = 0;
};

int N;
vector<int> A;

map<int, int> target;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    target.clear();

    int pref = 0;
    ll ans = 0;
    ll total = 0;
    for (int i = 0; i < N; i++) {
        // Insert at pref
        target[pref]++;
        total += i - 1;

        pref ^= A[i];

        ans += (ll)(i + 1) * i - total;
        ans -= (ll)target[pref] * (target[pref] + 1) / 2;
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        printf("Case #%d: ", i + 1);
        solve();
    }

    return 0;
}