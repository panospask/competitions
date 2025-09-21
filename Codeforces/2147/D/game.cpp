#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

int N;
map<int, int> cnt;

void solve(void) {
    scanf("%d", &N);

    cnt.clear();
    for (int i = 0; i < N; i++) {
        int v;
        scanf("%d", &v);

        cnt[v]++;
    }

    ll a = 0, b = 0;
    vector<int> odd;
    for (auto [v, c] : cnt) {
        int r = v;
        if (v % 2) {
            odd.push_back(c);
            r--;
        }

        a += (ll)r / 2 * c;
        b += (ll)r / 2 * c;
    }

    sort(odd.rbegin(), odd.rend());
    for (int i = 0; i < odd.size(); i++) {
        if (i % 2 == 0) {
            a += odd[i];
        }
        else {
            b += odd[i];
        }
    }
    printf("%lld %lld\n", a, b);

    return;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}