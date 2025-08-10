#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
const int LOG = 32;


int N, K;
vector<int> s;
vector<ll> effects;
vector<ll> operations;

void solve(void) {
    scanf("%d %d", &N, &K);

    s.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &s[i]);
    }
    sort(s.rbegin(), s.rend());

    ll ans = 1;
    while (K) {
        int v = s.back();
        s.pop_back();

        if (v <= LOG && K >= operations[v]) {
            K -= operations[v];
            ans = ans * effects[v] % MOD;
            continue;
        }

        ans = ans * v % MOD;
        K--;
        for (int i = min(v - 1, LOG); i > 0; i--) {
            s.push_back(i);
        }
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    effects.resize(LOG + 1);
    operations.resize(LOG + 1);
    effects[1] = 1;
    operations[1] = 1;
    for (int i = 2; i <= LOG; i++) {
        effects[i] = i;
        operations[i] = 1;
        for (int j = i - 1; j > 0; j--) {
            effects[i] = effects[i] * effects[j] % MOD;
            operations[i] += operations[j];
        }
    }

    while (t--) {
        solve();
    }

    return 0;
}