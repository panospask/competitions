#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M;
vector<int> a, b;
vector<int> res;

int main(void)
{
    scanf("%d %d", &N, &M);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    b.resize(M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &b[i]);
    }

    res.assign(N, 0);
    int j = 0;
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        while (j < M && b[j] < a[i]) {
            j++;
        }
        while (j < M && b[j] == a[i]) {
            res[i]++;
            j++;
        }

        ans += res[i];

        if (i < N - 1 && a[i + 1] == a[i]) {
            res[i + 1] = res[i];
        }
    }

    printf("%lld\n", ans);

    return 0;
}