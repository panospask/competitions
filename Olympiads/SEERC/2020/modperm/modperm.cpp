#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

int N;

int main(void)
{
    scanf("%d", &N);

    ll v = 1;
    for (int i = 0; i < N - 2; i++) {
        v = (v * 2) % MOD;
    }
    v = (v * N) % MOD;

    printf("%lld\n", v);

    return 0;
}