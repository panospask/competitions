#include <bits/stdc++.h>

using namespace std;

int N, T;
vector<int> a;

int main(void)
{
    scanf("%d %d", &N, &T);

    a.resize(N);
    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);

    int time = 0;
    int r = 0;
    int ans = 0;

    for (int l = 0; l < N; l++) {
        while (r < N && time + a[r] <= T) {
            time += a[r];
            r++;
        }

        ans = max(ans, r - l);

        time -= a[l];
    }

    printf("%d\n", ans);

    return 0;
}