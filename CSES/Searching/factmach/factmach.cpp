#include <bits/stdc++.h>

using namespace std;

int n, t;
int a[200000 + 5];

bool can_make_in(long long int x)
{
    long long int s = 0;
    for (int i = 0; i < n && s < t; i++) {
        s += x / a[i];
    }
    return s >= t;
}

int main(void)
{
    scanf("%d %d", &n, &t);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    long long int l = 0; //can_make_in(l) = false  
    long long int r = 1; //can_make_in(r) = true
    while (!can_make_in(r)) {
        l = r;
        r *= 2;
    }
    while (r > l + 1) {
        auto mid = (l + r) / 2;
        if (!can_make_in(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%lld\n", r);
    return 0;
}