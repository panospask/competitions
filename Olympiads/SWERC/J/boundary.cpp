#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

ll W, L;

void solve(void) {
    scanf("%d %d", &W, &L);

    vector<int> ans;
    ans.pb(1);
    ans.pb(2);

    for (int d = -1; d <= 1; d++) {
        ll a = (W - 1) + d;
        ll b = (L - 1) - d;
        
        for (ll v = 1; v * v <= a; v++) {
            if (a % v == 0) {
                ll v1 = v;
                ll v2 = a / v;

                if (b % v1 == 0) {
                    ans.pb(v1);
                }
                if (b % v2 == 0) {
                    ans.pb(v2);
                }
            }
        }
    }

    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
    printf("%d ", (int)ans.size());
    for (int i = 0; i < ans.size(); i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}