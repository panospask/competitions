#include <bits/stdc++.h>
#define MAXN 1e9

using namespace std;

int n, w, h;

bool can_fit(long long int x)
{
    long long int vert_fit = x / h; // How many recs can fit vertically
    long long int hor_fit = x / w; // How many recs can fit horizontally

    return vert_fit * hor_fit >= n;
}

int main(void)
{
    scanf("%d %d %d", &h, &w, &n);

    long long int l = 0;
    long long int r = 1;
    while (!can_fit(r)) {
        l = r;
        r *= 2;
    }

    // Invariants: can_fit(l) = false, can_fit(r) = true
    while (r > l + 1) {
        long long int mid = (l + r) / 2;
        if (!can_fit(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%lld\n", r);
    return 0;
}