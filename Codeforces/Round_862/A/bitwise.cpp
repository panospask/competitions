#include <bits/stdc++.h>
#define MAXN 1000

using namespace std;

int n, t;

int a[MAXN + 2];

void solve(void)
{
    scanf("%d", &n);
    int total_xor = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        total_xor = total_xor ^ a[i];
    }

    if (n % 2 == 0) {
        printf("%d\n", (total_xor == 0 ? 0 : -1));
    }
    else 
        printf("%d\n", total_xor);
}

int main(void)
{
    scanf("%d", &t);
    while (t--)
        solve();

    return 0;
}
