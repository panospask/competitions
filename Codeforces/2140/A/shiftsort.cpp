#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;
// pref[i] represents [0, i)
vector<int> pref;
// suff[i] represents [i, N)
vector<int> suff;

void solve(void) {
    scanf("%d", &N);

    a.resize(N);
    pref.resize(N + 1);
    suff.resize(N + 1);
    for (int i = 0; i < N; i++) {
        scanf("%1d", &a[i]);
    }
    
    bool one = false;
    pref[0] = 0;
    for (int i = 0; i < N; i++) {
        pref[i + 1] = pref[i] + (a[i] == 1);
    }

    bool zero = false;
    suff[N] = 0;
    for (int i = N - 1; i >= 0; i--) {
        suff[i] = suff[i + 1] + (a[i] == 0);
    }

    int ans = 0;
    for (int i = 0; i < suff[0]; i++) {
        ans += (a[i] == 1);
    }

    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}