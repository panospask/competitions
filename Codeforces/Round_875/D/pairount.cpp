#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
vector<int> a;
vector<int> b;
vector<vector<int>> freq;

void solve(void)
{
    scanf("%d", &n);
    int lim = sqrt(2 * n) + 1;

    freq.clear();
    freq.resize(lim, vector<int>(n + 1));
    a.resize(n);
    b.resize(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);

        if (a[i] < lim)
            freq[a[i]][b[i]]++;
    }

    ll ans = 0;
    for (int i = 0; i < n; i++)
        for (int aj = 1; aj < min(a[i], lim); aj++) {
            // Find pairs with a[i], j;

            int search = (a[i] * aj - b[i]);
            if (search > 0 && search <= n)
                ans += freq[aj][search];
        }

    // Now count pairs with same ai
    for (int ai = 1; ai < lim; ai++) {
        ll initital = ai * ai;
        for (int bi = 1; bi <= n; bi++) {
            ll bj = initital - bi;
            if (bj > bi && bj <= n) {
                ans += freq[ai][bi] * (ll)freq[ai][bj];
            }
            else if (bj == bi) {
                ans += (ll)freq[ai][bi] * (freq[ai][bi] - 1) / 2;
            }
        }
    }

    printf("%lld\n", ans);
    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();

    return 0;
}