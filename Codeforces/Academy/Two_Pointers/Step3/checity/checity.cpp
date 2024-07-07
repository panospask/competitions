#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, R;
vector<int> d;

int main(void)
{
    scanf("%d %d", &N, &R);

    d.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &d[i]);
    }

    ll ans = 0;
    int r = 0;
    for (int l = 0; l < N; l++) {
        while (r < N && d[r] - d[l] <= R) {
            r++;
        }

        ans += N - r;
    }

    printf("%lld\n", ans);  

    return 0;
}