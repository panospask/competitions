#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int main(void)
{
    freopen("similarity.in", "r", stdin);
    freopen("similarity.out", "w", stdout);

    vector<int> l1;
    vector<int> l2;

    map<int, int> cnt;

    int v1, v2;
    while (scanf("%d %d", &v1, &v2) != EOF) {
        l1.pb(v1);
        l2.pb(v2);
    }

    long long ans = 0;

    for (int i = 0; i < l2.size(); i++) {
        cnt[l2[i]]++;
    }
    for (int i = 0; i < l1.size(); i++) {
        ans += (long long)cnt[l1[i]] * l1[i];
    }

    printf("%lld\n", ans);

    return 0;
}