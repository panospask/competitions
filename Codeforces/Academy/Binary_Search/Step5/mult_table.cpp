#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

long long int n, k;

long long int count_before_or_eq(long long int x)
{
    long long int total = 0;
    for (int i = 1; i <= n; i++) {
        total += min((long long int)n, x / i);
    }

    return total;
}

bool is_before(long long int x)
{
    return count_before_or_eq(x) < k;
}

int main(void)
{
    scanf("%lld %lld", &n, &k);

    long long int r = n * (long long int)n; // is_before(r) = false
    long long int l = 0; // is_before(l) = true

    while (r > l + 1) {
        auto mid = (r + l) / 2;
        if (is_before(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%lld\n", r);
    return 0;
}