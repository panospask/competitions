#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int n, k;
int a[MAXN + 5];

// Total number of segments needed to make the max sum less than s(-1 if impossible)
int segments_needed(long long int s)
{
    long long int cursum = 0;
    int curseg = 1;
    for (int i = 0; i < n; i++) {
        if (a[i] > s)
            return -1;
        
        if (cursum + a[i] > s) {
            cursum = 0;
            curseg++;
        }
        cursum += a[i];
    }

    return curseg;
}

// If you can make k or less segments, the maximum sum of one being less than or equal to x
bool can_make(long long int x)
{
    int res = segments_needed(x);
    return (res != -1 && res <= k);
}

int main(void)
{
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    long long int l = 0; // can_make(l) = false
    long long int r = 1; // can_make(r) = true
    while (!can_make(r)) {
        l = r;
        r *= 2;
    }

    while (r > l + 1) {
        long long int mid = (l + r) / 2;
        if (!can_make(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%lld\n", r);
    return 0;
}