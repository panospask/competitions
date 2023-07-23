#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, k;
vector<ll> fib;

void solve(void)
{
    fib.clear();

    scanf("%d %d", &n, &k);


    k -= 2;
    fib.resize(2);
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i < k; i++) {
        fib.push_back(fib[i -1] + fib[i - 2]);
        if (fib[i] > n) {
            printf("0\n");
            return;
        }
    }

    ll a, b;
    if (k == 1) {
        a = b = 1;
    }
    else {
        a = fib[k - 2];
        b = fib[k - 1];
    }

    int r = n;
    int ans = 0;
    for (int l = 0; l <= n; l++) {
        // l as f1, r as  f2
        while (r > 0 && l * a + r * b > n)
            r--;
        if (l > r)
            break;

        if (l * a + r * b == n)
            ans++;
    }

    printf("%d\n", ans);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}