#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct State {
    int v;
    int num;
    int pref;
};

int N;
vector<int> a, b;

bool operator < (State a, State b) {
    if (a.v == b.v) {
        return a.pref < b.pref;
    }
    return a.v > b.v;
}

void solve(void) {
    scanf("%d", &N);

    a.resize(N);
    b.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }

    ll ans = 0;
    set<State> s;
    for (int i = 0; i < N; i++) {
        int remove = 0;
        while (!s.empty()) {
            State cur = *prev(s.end());
            if (cur.v >= a[i]) {
                break;
            }

            remove += cur.num;
            s.erase(cur);
        }

        int prv = 0;
        if (!s.empty()) {
            State cur = *prev(s.end());
            prv = cur.pref;
        }
        
        // We are to consider N - i different (right) endpoints of a subsegment
        if (b[i] == a[i]) {
            ans += (ll)(N - i) * (i + 1);
        }
        else {
            // We need to find positions s.t b[i] <= maximum
            auto it = s.upper_bound({b[i], 0, INT_MAX});
            int counted = 0;
            if (it != s.begin()) {
                counted = (*prev(it)).pref;
            }
            ans += (ll)(N - i) * counted;
        }

        // Update our set
        s.insert({a[i], remove + 1, prv + remove + 1});
    }

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