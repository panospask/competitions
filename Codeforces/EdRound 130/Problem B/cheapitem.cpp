#include <bits/stdc++.h>

using namespace std;

vector<int> price;
long long int pref_sum[200005];
int n, q;

int main(void)
{
    scanf("%d %d", &n, &q);
    price.resize(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &price[i]);
    }
    sort(price.rbegin(), price.rend());
    pref_sum[0] = price[0];
    for (int i = 1; i < n; i++) {
        pref_sum[i] = price[i] + pref_sum[i - 1];
    }

    for (int j = 0; j < q; j++) {
        int x, y;
        scanf("%d %d", &x, &y);

        long long int val;
        if (x != y)
            val = pref_sum[x - 1] - pref_sum[x - y - 1];
        else 
            val = pref_sum[x - 1];

        printf("%lld\n", val);
    }

    return 0;
}