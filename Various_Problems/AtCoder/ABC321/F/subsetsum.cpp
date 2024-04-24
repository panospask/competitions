#include <bits/stdc++.h>
#define MOD(a) (a = ((a % M) + M) % M)

using namespace std;

typedef long long ll;

const int M = 998244353;

int K, Q;
vector<ll> dp;

void add(int v)
{
    for (int i = K; i >= v; i--) {
        dp[i] += dp[i - v];
        MOD(dp[i]);
    }
}

void remove(int v)
{
    for (int i = v; i <= K; i++) {
        dp[i] -= dp[i - v];
        MOD(dp[i]);
    }
}

int main(void)
{
    scanf("%d %d", &Q, &K);

    dp.assign(K + 1, 0);
    dp[0] = 1;

    while (Q--) {
        char op;
        int s;
        scanf(" %c %d", &op, &s);

        if (op == '+') {
            add(s);
        }
        else {
            remove(s);
        }

        printf("%lld\n", dp[K]);
    }

    return 0;
}