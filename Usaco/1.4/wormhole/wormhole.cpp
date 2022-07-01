/*
ID: panos.p1
LANG: C++
TASK: wormhole
*/

#include <bits/stdc++.h>

using namespace std;

map<int, int> cnt;
set<int> exes;

int main(void)
{
    freopen("wormhole.in", "r", stdin);
    freopen("wormhole.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        cnt[y]++;
        exes.insert(y);
    }

    long long int ttl_count = 0;
    for (auto x : exes) {
        ttl_count += pow(2ll, (long long int)cnt[x]);
        ttl_count -= cnt[x] + 1;
    }

    printf("%lld\n", ttl_count);
    return 0;
}