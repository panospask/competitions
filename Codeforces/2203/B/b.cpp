#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void solve(void) {
    ll N;
    scanf("%lld", &N);

    vector<int> d;
    ll sum = 0;
    
    while (N) {
        d.push_back(N % 10);
        sum += d.back();
        N /= 10;
    }
    // Treat last digit specially, just ensure that it can be reduced to 1
    int l = d.back();
    d.pop_back();
    d.push_back(l - 1);

    sort(d.begin(), d.end());

    int ans = 0;
    while (sum >= 10) {
        ans++;
        sum -= d.back();
        d.pop_back();
    }

    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}