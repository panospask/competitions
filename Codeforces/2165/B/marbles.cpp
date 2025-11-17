#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int MOD = 998244353;

int N;
vector<int> A;
vector<pi> cnt;
vector<ll> suff;

vector<ll> mul;

// ways[i][k]: Ways to use the fist i values such that (sum of (number of modes)) = k
vector<vector<ll>> ways; 

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    cnt.clear();
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        A[i]--;
    }

    sort(A.begin(), A.end());
    int p = A[0];
    int c = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] != p) {
            cnt.pb(mp(c, p));
            p = A[i];
            c = 0;
        }
        c++;
    }
    cnt.pb(mp(c, p));
    sort(cnt.begin(), cnt.end());
    
    int M = cnt.size();
    cnt.pb(mp(0, -1));
    
    ways.assign(M + 1, vector<ll>(N + 1, 0));
    suff.assign(M + 1, 0);
    mul.assign(M + 1, 1);

    mul[M] = 1;
    suff[M] = 0;
    for (int i = M - 1; i >= 0; i--) {
        suff[i] = (suff[i + 1] + cnt[i + 1].first) % MOD;
        if (i == M - 1) {
            mul[i] = 1;
        }
        else {
            mul[i] = (mul[i + 1] * cnt[i + 1].first) % MOD;
        }
    }

    ll ans = 0;
    ways[0][0] = 1;
    for (int i = 0; i < M; i++) {
        int c = cnt[i].first;

        // Assuming this value won't be used but everything after will, update answer
        int needed = max(c - suff[i], 0LL);
        for (int k = needed; k <= N; k++) {
            ans += ways[i][k] * mul[i] % MOD;
            ans %= MOD;
        }

        // We can choose to actually use the value cnt[i].second, we have c possibilities
        for (int k = c; k <= N; k++) {
            ways[i + 1][k] += (ll)c * ways[i][k - c] % MOD;
            ways[i + 1][k] %= MOD;
        }

        // Or we can choose not to use it
        for (int k = 0; k <= N; k++) {
            ways[i + 1][k] += ways[i][k];
            ways[i + 1][k] %= MOD;
        }
    }

    // Don't forget to include case where all are used
    ll res = 1;
    for (int i = 0; i < M; i++) {
        res = res * cnt[i].first % MOD;
    }
    ans = (ans + res) % MOD;

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