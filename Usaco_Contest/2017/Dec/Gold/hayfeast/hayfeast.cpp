#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

int n;
vector<int> f;
vector<int> s;
ll m;

int main(void)
{
    freopen("hayfeast.in", "r", stdin);
    freopen("hayfeast.out", "w", stdout);

    scanf("%d %lld", &n, &m);
    f.resize(n + 1);
    s.resize(n + 1);

    for (int i = 1; i <= n; i++)
        scanf("%d %d", &f[i], &s[i]);

    ll total_flavour = 0;
    int l = 0, r = 1;
    ll ans = INT_MAX;
    multiset<int> spice;
    spice.insert(0);

    while (l <= n) {
        spice.erase(spice.find(s[l]));
        total_flavour -= f[l];

        while (r <= n && total_flavour < m) {
            spice.insert(s[r]);
            total_flavour += f[r];
            r++;
        }

        if (total_flavour >= m)
            ans = min((int)ans, *spice.rbegin());
        l++;
    }

    printf("%lld\n", ans);
    return 0;
}