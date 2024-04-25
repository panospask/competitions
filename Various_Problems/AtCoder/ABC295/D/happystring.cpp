#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int DIGITS = 10;

int N;
string a;

// cnt[s] represents the number of positions that have s as the set of parities
int cnt[1ll << DIGITS];

int main(void)
{
    cin >> a;

    cnt[0] = 1;
    ll curset = 0;
    ll ans = 0;
    for (int i = 0; i < a.size(); i++) {
        int v = a[i] - '0';

        curset = curset ^ (1ll << v);
        ans += cnt[curset];
        cnt[curset]++;
    }

    printf("%lld\n", ans);

    return 0;
}