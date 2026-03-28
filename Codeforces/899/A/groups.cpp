#include <bits/stdc++.h>

using namespace std;

int N;

int main(void) {
    scanf("%d", &N);

    int x1 = 0, x2 = 0;
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);

        if (x == 1) {
            x1++;
        }
        else {
            x2++;
        }
    }

    int ans = min(x1, x2);
    x1 -= ans;
    x2 -= ans;

    ans += x1 / 3;

    printf("%d\n", ans);
}
