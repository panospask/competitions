#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(void)
{
    while (true) {
        long long int N, M;
        scanf("%lld %lld", &M, &N);

        if (N == 0 && M == 0)
            break;

        double ans = 0;
        if (N < M)
            ans = 0;
        else
            ans = (N + 1 - M) / (double)(N + 1);

        printf("%.6lf\n", ans);
    }
}