#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;
vector<int> pref;
vector<int> suff;

void solve(void)
{
    scanf("%d", &N);

    a.resize(N);
    pref.resize(N);
    suff.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    pref[0] = 0;
    for (int i = 1; i < N; i++) {
        pref[i] = max(pref[i - 1], a[i - 1]) - 1;
    }
    suff[N - 1] = 0;
    for (int i = N - 2; i >= 0; i--) {
        suff[i] = max(suff[i + 1], a[i + 1]) - 1;
    }

    int ans = 0;
    for (int i = 1; i < N - 1; i++) {
        ans = max(ans, a[i] + pref[i] + suff[i]);
    }

    printf("%d\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}