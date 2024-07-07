#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M, S, A, B;
vector<int> a, b;

int main(void)
{
    scanf("%d %d %d %d %d", &N, &M, &S, &A, &B);

    a.resize(N);
    b.resize(M);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    sort(a.rbegin(), a.rend());
    for (int i = 0; i < M; i++) {
        scanf("%d", &b[i]);
    }
    sort(b.begin(), b.end());

    int p2 = 0;
    ll w = (ll)M * B;
    ll cur = 0, ans = 0;
    for (int i = 0; i < M; i++) {
        cur += b[i];
    }

    for (int p1 = 0; p1 < N + 1; p1++) {
        while (p2 < M && w > S) {
            w -= B;
            cur -= b[p2];
            p2++;
        }

        if (w <= S) {
            ans = max(ans, cur);
        }

        if (p1 != N) {
            w += A;
            cur += a[p1];
        }
    }

    printf("%lld\n", ans);

    return 0;
}