#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, S;
vector<int> c, w;

int main(void)
{
    scanf("%d %d", &N, &S);

    c.resize(N);
    w.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &w[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &c[i]);
    }

    int r = 0;
    ll curw = 0, curc = 0;
    ll ans = 0;

    for (int l = 0; l < N; l++) {
        while (r < N && curw + w[r] <= S) {
            curw += w[r];
            curc += c[r];
            r++;
        }

        ans = max(ans, curc);

        curw -= w[l];
        curc -= c[l];
    }

    printf("%lld\n", ans);

    return 0;
}