#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int main(void)
{
    freopen("distances.in", "r", stdin);
    freopen("distances.out", "w", stdout);

    vector<int> l1;
    vector<int> l2;

    int v1, v2;
    while (scanf("%d %d", &v1, &v2) != EOF) {
        l1.pb(v1);
        l2.pb(v2);
    }

    sort(l1.begin(), l1.end());
    sort(l2.begin(), l2.end());

    long long ans = 0;
    for (int i = 0; i < l1.size(); i++) {
        ans += abs(l1[i] - l2[i]);
    }

    printf("%lld\n", ans);

    return 0;
}