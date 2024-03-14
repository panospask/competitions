#include <bits/stdc++.h>

using namespace std;

int a[100005];

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        int n;
        scanf("%d", &n);

        int odd = 0; int even = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            if (a[i] % 2)
                odd++;
            else 
                even++;
        }

        printf("%d\n", min(odd, even));
    }

    return 0;
}