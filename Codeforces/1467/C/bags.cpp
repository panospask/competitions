#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> sum;
vector<vector<int>> bags;

ll test(int a, int b, int c) {
    ll res = sum[a];

    ll c1 = sum[b] + sum[c] - 2 * bags[b].front() - 2 * bags[c].front();
    ll c2 = sum[b] - sum[c];
    ll c3 = sum[c] - sum[b];

    return res + max(c1, max(c2, c3));
}

int main(void) {
    bags.resize(3);
    sum.resize(3);
    for (int i = 0; i < 3; i++) {
        int x;
        scanf("%d", &x);
        bags[i].resize(x);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < bags[i].size(); j++) {
            scanf("%d", &bags[i][j]);
            sum[i] += bags[i][j];
        }
        sort(bags[i].begin(), bags[i].end());
    }

    ll ans = 0;
    for (int i = 0; i < 3; i++) {
        ans = max(ans, test(i, (i + 1) % 3, (i + 2) % 3));
    }

    printf("%lld\n", ans);
}