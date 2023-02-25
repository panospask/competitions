#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int n;
long long int k;
long long int a[MAXN + 5], b[MAXN + 5];

long long int count_before_or_eq(long long int x)
{
    long long int total = 0;
    int cur_b = n - 1;
    for (int i = 0; i < n && cur_b >= 0; i++) {
        while (cur_b >= 0 && a[i] + b[cur_b] > x)
            cur_b--;
        total += cur_b + 1;
    }

    return total;
}

bool is_before(long long int x)
{
    return count_before_or_eq(x) < k;
}

int main(void)
{
    scanf("%d %lld", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &b[i]);
    }
    sort(a, a + n);
    sort(b, b + n);

    long long int l = 0; // is_before(l) = true
    long long int r = a[n-1] * b[n-1]; // is_before(r) = false
    while (r > l + 1) {
        auto mid = (l + r) / 2;
        if (is_before(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%lld\n", r);
    return 0;
}