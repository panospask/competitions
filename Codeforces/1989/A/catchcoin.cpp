#include <bits/stdc++.h>

using namespace std;

int N;

void solve(void)
{
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d %d", &x, &y);


        if (abs(x) > y + abs(x) + 1) {
            printf("NO\n");
        }
        else {
            printf("YES\n");
        }
    }
}

int main(void)
{
    int t = 1;

    while (t--) {
        solve();
    }

    return 0;
}