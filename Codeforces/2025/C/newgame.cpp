#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N, K;
vector<int> a, cords, cnt;

int code(int v)
{
    return lower_bound(cords.begin(), cords.end(), v) - cords.begin();
}

void solve(void)
{
    scanf("%d %d", &N, &K);

    a.resize(N);
    cords.clear();

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        cords.pb(a[i]);
    }

    sort(cords.begin(), cords.end());
    cords.resize(unique(cords.begin(), cords.end()) - cords.begin());

    cnt.assign(cords.size(), 0);
    for (int i = 0; i < N; i++) {
        cnt[code(a[i])]++;
    }

    int p = -1;
    int sum = 0;
    int ans = 0;
    for (int i = 0; i < cords.size(); i++) {
        if (p < i) {
            p = i;
            sum = cnt[i];
        }

        while (p + 1 < cords.size() && cords[p + 1] == cords[p] + 1 && cords[p + 1] - cords[i] < K) {
            p++;
            sum += cnt[p];
        }

        ans = max(ans, sum);

        sum -= cnt[i];
    }

    printf("%d\n", ans);
}

int main(void)
{
    int t;

    scanf("%d", &t);
    while (t--) {
        solve();
    }

    return 0;
}