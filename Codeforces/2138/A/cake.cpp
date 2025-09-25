#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

ll K, X;
vector<int> ans;

void solve(void) {
    scanf("%lld %lld", &K, &X);

    ll a = X, b = (1LL << (K + 1)) - X;
    ans.clear();

    while (a != b) {
        bool swapped = a > b;
        
        if (swapped) {
            swap(a, b);
        }

        ll prva = 2 * a;
        ll prvb = b - a;

        a = prva;
        b = prvb;

        if (swapped) {
            swap(a, b);
        }

        ans.pb(swapped);
    }

    reverse(ans.begin(), ans.end());

    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++) {
        printf("%d ", ans[i] + 1);
    }
    printf("\n");

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