#include <bits/stdc++.h>

using namespace std;

void solve(int a, int b, int c)
{
    int x = c + a + b;
    int y = c + b;
    int z = c;

    printf("%d %d %d\n", x, y, z);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        solve(a, b, c);
    }

    return 0;
}