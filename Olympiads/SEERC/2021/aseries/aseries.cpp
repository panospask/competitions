#include <bits/stdc++.h>

using namespace std;

int N;

vector<long long> a, b;

int main(void)
{
    scanf("%d", &N);

    a.resize(N + 1);
    b.resize(N + 1);

    for (int i = 0; i <= N; i++) {
        scanf("%lld", &a[i]);
    }
    for (int i = 0; i <= N; i++) {
        scanf("%lld", &b[i]);
    }

    long long ans = 0;
    for (int i = N; i > 0; i--) {
        if (a[i] < b[i]) {
            int wanted = b[i] - a[i];

            b[i - 1] += (wanted + 1) / 2;
            ans += (wanted + 1) / 2;
        }
    }

    if (a[0] < b[0]) {
        printf("-1\n");
    }
    else {
        printf("%lld\n", ans);
    }

    return 0;
}