#include <bits/stdc++.h>

using namespace std;

void solve(void)
{
    int a, b, c;

    scanf("%d %d %d", &a, &b, &c);

    if (a + 1 != c) {
        printf("-1\n");
        return;
    }

    int h = 0;
    int s_b = 0;
    while (a) {
        int rm = min((1 << h), a);
        s_b = (1 << h) - rm;
        a -= rm;
        h++;
    }

    int xtra_lev = b / c;
    int add_more = b % c;

    int ans = h + xtra_lev;
    if (add_more > s_b)
        ans++;

    printf("%d\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}