#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Line {
    ll a, b;
    
    ll eval(ll x) {
        return a * x + b;
    }
};

const ll INF = 1e18;

int N, K;
vector<int> R;

vector<ll> pref;
vector<ll> mulpref;

// dp[k][i]: Deal with elements [1, i] using k doors
vector<vector<ll>> dp;

deque<Line> hull;

ll ceil(ll a, ll b) {
    return (a + b - 1) / b;
}

// Return first integer point after intersection
ll intersect(Line l1, Line l2) {
    return ceil(l2.b - l1.b, l1.a - l2.a);
}

ll test(void){
    dp.assign(K + 1, vector<ll>(N + 1, INF));
    pref[0] = mulpref[0] = 0;
    for (int i = 1; i <= N; i++) {
        pref[i] = R[i] + pref[i - 1];
        mulpref[i] = (ll)i * R[i] + mulpref[i - 1];
    }
   
    for (int k = 1; k <= K; k++) {
        hull.clear();
        hull.push_back({-1, 0});
        for (int i = 1; i <= N; i++) {
            while (hull.size() >= 2) {
                if (hull[0].eval(pref[i]) >= hull[1].eval(pref[i])) {
                    hull.pop_front();
                }
                else {
                    break;
                }
            }

            dp[k][i] = mulpref[i] + hull[0].eval(pref[i]);

            if (dp[k - 1][i] == INF) {
                continue;
            }
            
            Line cur = {-(i+1), dp[k - 1][i] - mulpref[i] + (i + 1) * pref[i]};
            int sz = hull.size();
            while (sz >= 2) {
                if (intersect(hull[sz - 2], hull[sz - 1]) >= intersect(hull[sz - 1], cur)) {
                    hull.pop_back();
                    sz--;
                }
                else {
                    break;
                }
            }
            hull.push_back(cur);
        }
    }

    return dp[K][N];
}

int main(void) {
    freopen("cbarn.in", "r", stdin);
    freopen("cbarn.out", "w", stdout);

    scanf("%d %d", &N, &K);

    R.resize(N + 1);
    pref.resize(N + 1);
    mulpref.resize(N + 1);
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &R[i]);
    }

    ll ans = INF;
    for (int i = 1; i <= N; i++) {
        int t = R[1];
        R.erase(R.begin() + 1);
        R.push_back(t);

        ans = min(ans, test());
    }   

    printf("%lld\n", ans);
}