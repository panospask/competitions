#include <bits/stdc++.h>

using namespace std;

int ask(int a, int b)
{
    printf("? %d %d\n", a, b);
    fflush(stdout);

    int res;
    scanf("%d", &res);

    return res;
}

void solve(void)
{
    int l = 1; // Always reported right
    int r = 999; // Always reported wrong

    while (l + 1 < r) {
        int m1 = (l + l + r) / 3;
        int m2 = (l + r + r) / 3;

        int res = ask(m1, m2);

        if (res == m1 * m2) {
            l = m2;
        }
        else if (res == m1 * m2 + m1) {
            l = m1;
            r = m2;
        }
        else {
            r = m1;
        }
    }

    printf("! %d\n", r);

    return;
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