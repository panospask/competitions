#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

int N;
vector<int> A;
vector<int> prv, nxt;
set<pair<int, pi>> cost;

pair<int, pi> combine(int l, int r) {
    return mp(max(A[l], A[r]), mp(l, r));
}

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    prv.resize(N);
    nxt.resize(N);
    cost.clear();

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        prv[i] = i - 1;
        nxt[i] = i + 1;
    }
    prv[0] = N - 1;
    nxt[N - 1] = 0;

    for (int i = 0; i < N; i++) {
        cost.insert(combine(prv[i], i));
    }

    ll ans = 0;
    for (int i = 0; i < N - 1; i++) {
        auto p = *cost.begin();
        cost.erase(cost.begin());

        ans += p.first;
        int a = p.second.first;
        int b = p.second.second;        

        // Erase left of a and right of b
        cost.erase(combine(prv[a], a));
        cost.erase(combine(b, nxt[b]));
    
        // Assume a will be representative from now on
        A[a] = max(A[a], A[b]);
        prv[nxt[b]] = a;
        nxt[a] = nxt[b];
        cost.insert(combine(prv[a], a));
        cost.insert(combine(a, nxt[a]));
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