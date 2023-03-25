#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int a[MAXN + 5];
int n, k;

bool can_have_max_sum(long long int s)
{
    int divs_rem = k - 1;
    long long int cur_sum = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > s) return false;

        if (cur_sum + a[i] > s) {
            divs_rem--;
            cur_sum = 0;
        }
        cur_sum += a[i];
    }

    return divs_rem >= 0;
}

int main(void)
{
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    long long int l = 0; // can_have_max_sum(l) = false
    long long int r = 1; // can_have_max_sum(r) = true 
    while (!can_have_max_sum(r)) {
        l = r;
        r *= 2;
    }   
    while (r > l + 1) {
        auto mid = (l + r) / 2;
        if (can_have_max_sum(mid))
            r = mid;
        else 
            l = mid;
    }

    printf("%lld\n", r);
    return 0;
}