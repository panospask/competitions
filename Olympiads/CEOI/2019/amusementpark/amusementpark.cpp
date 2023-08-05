#include <bits/stdc++.h>
#define pb push_back
#define CHECK_BIT(val, pos) (val & (1 << pos))

using namespace std;

const int MOD = 998244353;
const int INV2 = 499122177;

typedef long long ll;

int N, M;
vector<int> adj_list;

// dp[s]: # of ways to construct a DAG in our graph, by directing some of the edges
vector<int> dp;
vector<bool> isgood;

void add(int& a, int b)
{
    a += b;
    if (a > MOD)
        a -= MOD;
}

void subtract(int& a, int b)
{
    a -= b;
    if (a < 0)
        a += MOD;
}

int main(void)
{
    scanf("%d %d", &N, &M);

    adj_list.resize(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u] |= (1 << v);
        adj_list[v] |= (1 << u);
    }

    isgood.resize(1 << N);
    dp.resize(1 << N);
    for (int s = 0; s < 1 << N; s++) {
        isgood[s] = true;
        for (int i = 0; i < N; i++) {
            if (CHECK_BIT(s, i))
                isgood[s] = isgood[s] && ((adj_list[i] & s) == 0);
        }
    }

    dp[0] = 1;
    for (int s = 1; s < 1 << N; s++) {
        dp[s] = 0;
        if (__builtin_popcount(s) == 1) {
            dp[s] = 1;
            continue;
        }
        for (int p = s; p > 0; p = (p - 1) & s) {
            if (!isgood[p])
                continue;

            if (__builtin_popcount(p) % 2)
                add(dp[s], dp[s - p]);
            else
                subtract(dp[s], dp[s - p]);
        }
    }

    int ans = ((ll)M * dp[(1 << N) - 1] % MOD * (ll)INV2) % MOD;

    printf("%d\n", ans);

    return 0;
}