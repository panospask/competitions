#include <bits/stdc++.h>

using namespace std;

long long int n;

// Returns true if x is before the (n/2) element, false otherwise
bool is_before(long long int x)
{
    long long int s = 0;
    for (int i = 1; i <= n && s < n * n / 2 + 1; i++)
        s += min((long long int)n, x/ i);

    return s < n * n / 2 + 1;
}

int main(void)
{
    scanf("%lld", &n);
    long long int l = 0; //is_before(l) = true
    long long int r = 1; //is_before(r) = false
    while (is_before(r)) {
        l = r;
        r *= 2;
    }
    while (r > l + 1) {
        auto m = (r + l) / 2;
        if (is_before(m))
            l = m;
        else 
            r = m;
    }

    printf("%lld\n", r);
}