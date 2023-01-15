#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int gcd_frwd[MAXN + 5];
int gcd_bcwd[MAXN + 5];
int n;
int arr[MAXN + 5];

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    gcd_frwd[0] = arr[0];
    for (int i = 1; i < n; i++)
        gcd_frwd[i] = gcd(gcd_frwd[i - 1], arr[i]);
    gcd_bcwd[n - 1] = arr[n - 1];
    for (int i = n - 2; i >= 0; i--)
        gcd_bcwd[i] = gcd(gcd_bcwd[i + 1], arr[i]);

    int ans = gcd_frwd[n - 1];
    int prevnums;
    int nextnums;
    
    // Check for number at pos 0
    ans = max(ans, gcd_bcwd[1]);

    // Check for number at pos n - 1
    ans = max(ans, gcd_frwd[n - 2]);

    for (int i = 1; i < n - 1; i++) {
        prevnums = gcd_frwd[i - 1];
        nextnums = gcd_bcwd[i + 1];

        ans = max(ans, gcd(prevnums, nextnums));
    }

    printf("%d\n", ans);
    return 0;
}