#include <bits/stdc++.h>
#define pf push_front

using namespace std;

typedef long long ll;

ll ceil(ll a, ll b) {
    return (a + b - 1) / b;
}

struct Line {
    ll a, b;

    ll eval(ll x) {
        return a * x + b;
    }
    
    // First integer x after (to the right) of intersection of l and *this
    ll intersect(Line l) {
        return ceil(l.b - b, a - l.a);
    }
};

int N;
vector<int> A;
vector<ll> pref, mulpref;

deque<Line> hull;

// Find optimal line of the hull that maximizes value at x using binary search
ll find_hull(ll x) {
    int l = 0; // l <= opt
    int r = hull.size();

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (hull[mid].eval(x) >= hull[mid - 1].eval(x)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    return hull[l].eval(x);
}

int main(void) {
    scanf("%d", &N);

    A.resize(N + 1);
    pref.resize(N + 1);
    mulpref.resize(N + 1);

    pref[0] = mulpref[0] = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    
        pref[i] = pref[i - 1] + A[i];
        mulpref[i] = (ll)i * A[i] + mulpref[i - 1];
    }

    hull.pf({0, 0});
    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        ans = max(ans, mulpref[i] + find_hull(pref[i]));

        Line cur = {-i, -mulpref[i] + i * pref[i]};
        while (hull.size() >= 2) {
            if (hull[0].intersect(hull[1]) <= cur.intersect(hull[0])) {
                // hull[1] starts winning over hull[0] before hull[0] starts winning over cur
                hull.pop_front();
            }
            else {
                break;
            }
        }
        hull.push_front(cur);
    }

    printf("%lld\n", ans);
}