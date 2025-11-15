#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

const ll INF = 1e18;

struct Line {
    ll a, b;

    ll eval(ll v) {
        return a * v + b;
    }
    long double intersectX(Line l) {
        return (long double)(l.b - b) / (a - l.a);
    }
};

int N, K;
vector<int> C;

// dp[l][i]: Minimum cost to deal with the first i houses using l schools
vector<vector<ll>> dp;
// place[l][i]: Minimum cost to deal with the first i houses using l schools **but** school l is placed on house i
vector<vector<ll>> place;

vector<ll> pref;
vector<ll> mulpref;

// We assume queries come in increasing order and slopes come in decreasing order
deque<Line> hull;

void clear(void) {
    hull.clear();
}

// Insert line of the form ax + b
void insert(Line l) {
    int sz = hull.size();
    while (sz >= 2) {
        if (hull[sz - 2].intersectX(l) >= hull[sz - 1].intersectX(l)) {
            hull.pop_back();
            sz--;
        }
        else {
            break;
        }
    }

    hull.push_back(l);
}

ll query(ll v) {
    while (hull.size() >= 2) {
        if (hull[0].eval(v) >= hull[1].eval(v)) {
            // First line is finished
            hull.pop_front();
        }
        else {
            break;
        }
    }

    return hull[0].eval(v);
}

int main(void) {
    scanf("%d %d", &N, &K);

    C.resize(N + 1);
    pref.resize(N + 1);
    mulpref.resize(N + 1);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &C[i]);

        pref[i] = pref[i - 1] + C[i];
        mulpref[i] = mulpref[i - 1] + (ll)i * C[i];
    }

    dp.assign(K + 1, vector<ll>(N + 1, INF));
    place.assign(K + 1, vector<ll>(N + 1, INF));
    dp[0][0] = 0;

    for (int l = 1; l <= K; l++) {
        clear();
        insert({0, 0});
        for (int i = 1; i <= N; i++) {
            ll res = query(i);
            place[l][i] = i * pref[i] - mulpref[i] + res;

            insert({-pref[i] , dp[l - 1][i] + mulpref[i]});
        }
        
        clear();
        for (int i = 1; i <= N; i++) {
            insert({-i, place[l][i] - mulpref[i] + i * pref[i]});

            ll res = query(pref[i]);
            dp[l][i] = mulpref[i] + res;
        }
    }

    printf("%lld\n", dp[K][N]);
}