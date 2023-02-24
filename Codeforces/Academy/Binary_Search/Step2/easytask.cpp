#include <bits/stdc++.h>
#define MAXN 2e8

using namespace std;

int n, x, y;

bool can_copy(long long int time)
{
    int copies_made_x = time / x;
    int copies_made_y = max(0ll, (time - x) / y);

    return copies_made_x + copies_made_y >= n;
}

int main(void)
{
    scanf("%d %d %d", &n, &x, &y);
    if (x > y)
        swap(x, y);

    
    long long int l = 0; // can_copy[l] = false
    
    long long int r = 2 * 1000000000; // can_copy[r] = true
    while (r > l + 1) {
        
        long long int mid = (l + r) / 2;
        if (!can_copy(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%lld\n", r);
}