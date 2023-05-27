#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, m;
vector<int> a;
vector<ll> d;

int main(void)
{
    scanf("%d %d", &n, &m);

    a.resize(n);
    d.assign(n+1, INT_MIN);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    d[0] = INT_MAX;
    for (int i = 0; i < n; i++) {
        ll curval = a[i] - m * (i + 1);
        if (curval > 0) {
            // We must modify this pillar, as we cannot reach it from the ground
            continue;
        }
        int l = 0;
        int r = n + 1;
        while (r > l + 1) {
            int mid = (l + r) / 2;
            if (d[mid] >= curval)
                l = mid;
            else
                r = mid;
        }

        d[l+1] = curval;
    }

    int ans = 0;
    for (int i = 0; i < n + 1; i++)
        if (d[i] != INT_MIN)
            ans = i;

    printf("%d\n", n - ans);
    return 0;
}