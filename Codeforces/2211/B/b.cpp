#include <bits/stdc++.h>

using namespace std;

int x, y;

void solve(void) {
    scanf("%d %d", &x, &y);

    int sum = abs(x - y);

    int ans = 0;
    if (sum == 0) {
        ans = 1;
    }
    else {
            for (int i = 1; i * i <= sum; i++) {
                if (sum % i == 0) {
                    ans++;
                    if (i * i != sum) {
                        ans++;
                    }
                }
            }
    }

    printf("%d\n", ans);
    for (int i = 0; i < x; i++) {
        printf("1 ");
    }
    for (int j = 0; j < y; j++) {
        printf("-1 ");
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}