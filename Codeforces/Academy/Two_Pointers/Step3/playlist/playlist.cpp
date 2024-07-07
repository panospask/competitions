#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> a;
ll P;

int main(void)
{
    scanf("%d %lld", &N, &P);

    a.resize(2 * N);
    ll totsum = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        totsum += a[i];
        a[i + N] = a[i];
    }

    ll base = P / totsum;
    P %= totsum;
    int after = N + 1;
    int start = 0;

    int r = 0;
    ll cursum = 0;
    for (int l = 0; l < N; l++) {
        while (cursum < P) {
            cursum += a[r];
            r++;
        }

        if (after > r - l) {
            after = r - l;
            start = l;
        }

        cursum -= a[l];
    }

    printf("%d %lld\n", start + 1, N * base + after);

    return 0;
}