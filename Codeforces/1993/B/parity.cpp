#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<ll> a;

void solve(void)
{
    scanf("%d", &N);

    a.resize(N);
    int even = 0;
    for (int i = 0; i < N; i++) {
        scanf("%lld", &a[i]);

        if (a[i] % 2 == 0) {
            even++;
        }
    }
    sort(a.begin(), a.end());

    if (even == N || even == 0) {
        printf("0\n");
        return;
    }

    ll bigodd = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] % 2) {
            bigodd = max(bigodd, a[i]);
        }
    }
    int ans = 0;
    bool use_more = false;
    for (int i = 0; i < N; i++) {
        if (a[i] % 2 == 0) {
            if (a[i] > bigodd) {
                use_more = true;
            }
            ans++;
            bigodd = a[i] + bigodd;
            a[i] = bigodd;
        }
    }
    ans += use_more;

    printf("%d\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while(t--) {
        solve();
    }

    return 0;
}