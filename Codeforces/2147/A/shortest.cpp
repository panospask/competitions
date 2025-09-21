#include <bits/stdc++.h>

using namespace std;

int X, Y;

void solve(void) {
    scanf("%d %d", &X, &Y);

    if (X < Y) {
        printf("2\n");
    }
    else if (X <= Y + 1 || Y == 1) {
        printf("-1\n");
    }
    else if (X > Y) {
        printf("3\n");
    }

    return;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}