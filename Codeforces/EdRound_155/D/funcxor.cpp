#include <bits/stdc++.h>
#define CHECK_BIT(val, pos) ((val & (1 << pos)) != 0)

using namespace std;

typedef long long ll;

const int MOD = 998244353;
const int MAXLOG = 30;

int N;
vector<int> a;

vector<int> active;

// Number of times the bit will be used in the sum with i first position
vector<ll> suff[2];
vector<ll> len[2];

ll process_bit(int b)
{
    active.resize(N + 1);
    active[0] = 0;
    for (int i = 0; i < N; i++)
        active[i + 1] = active[i] ^ CHECK_BIT(a[i], b);

    ll res = 0;
    suff[0].resize(N + 1);
    suff[1].resize(N + 1);
    len[0].resize(N + 1);
    len[1].resize(N + 1);

    suff[0][N] = suff[1][N] = 0;
    len[0][N] = len[1][N] = 0;
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < 2; j++) {
            suff[j][i] = suff[j][i + 1];
            len[j][i] = len[j][i + 1] + suff[j][i + 1];
        }

        suff[active[i + 1]][i]++;
        len[active[i + 1]][i]++;
    }

    for (int i = 0; i < N; i++)
        res += len[!active[i]][i];

    return res % MOD;
}

int main(void)
{
    scanf("%d", &N);

    a.resize(N);

    ll ans = 0;

    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);

    for (int b = 0; b < MAXLOG; b++) {
        ans += process_bit(b) * (1ll << b) % MOD;
        ans %= MOD;
    }

    printf("%lld\n", ans);

    return 0;
}