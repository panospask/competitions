#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXV = 1000;
const int MOD = 1000000;


int N;
vector<ll> c;

int main(void)
{
    c.assign(MAXV + 1, 0);

    c[0] = 1;
    for (int i = 1; i <= MAXV; i++) {
        for (int j = 0; j < i; j++) {
            c[i] += c[j] * c[i - j - 1] % MOD;
        }
        c[i] %= MOD;
    }

    scanf("%d", &N);
    while (N) {
        printf("%lld\n", c[N]);
        scanf("%d", &N);
    }

    return 0;
}