#include <bits/stdc++.h>

using namespace std;

int n;
void solve(void)
{
    scanf("%d", &n);
    if (n == 1) {
        printf("1\n");
        return;
    }
    if (n % 2) {
        printf("-1\n");
        return;
    }

    int big_even = n;
    int small_odd = 1;
    for (int i = 0; i < n; i++) {
        if (i % 2) {
            printf("%d ", i);
        }
        else {
            printf("%d ", i + 2);
        }
    }

    printf("\n");
    return;
}

int t;
int main(void)
{
    scanf("%d", &t);
    while (t--)
        solve();
}