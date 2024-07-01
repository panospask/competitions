#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXV = 1e6;
const int INF = 1e9;

int N, M;
vector<int> opt, tot;
vector<int> a, b, c;

int main(void)
{
    scanf("%d %d", &N, &M);

    a.resize(N);
    b.resize(N);
    c.resize(M);
    opt.assign(MAXV + 1, -INF);
    tot.assign(MAXV + 1, 0);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &c[i]);
    }

    for (int i = 0; i < N; i++) {
        opt[a[i]] = max(opt[a[i]], b[i] - a[i]);
    }
    for (int v = 1; v <= MAXV; v++) {
        opt[v] = max(opt[v], opt[v - 1]);
    }


    // Calculate total for each value in [0, MAXV]
    tot[0] = 0;
    for (int i = 0; i <= MAXV; i++) {
        if (opt[i] != -INF) {
            tot[i] = tot[i + opt[i]] + 2;
        }
    }

    int globalopt = opt[MAXV];

    ll ans = 0;
    for (int i = 0; i < M; i++) {
        int times = ((MAXV - c[i]) / globalopt) + 1;
        times = max(times, 0);

        c[i] += globalopt * times;
        ans += 2 * times + tot[c[i]];
    }

    printf("%lld\n", ans);

    return 0;
}