#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << pos))
#define pb push_back

using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
const int MAXN = 205;

int T, N, V;
vector<vector<int>> kids;
vector<int> subtree_size;
vector<int> par;

// Truth value used for case #1
bool creatable = true;

// Number of ways to create each subtree, used for case #2
vector<ll> ways;

// used for combinatorics
vector<ll> fact;
vector<ll> inv;

ll calc_power(ll a, ll b)
{
    ll c = 1;
    while (b) {
        if (b % 2) {
            c = c * a % MOD;
        }

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

void precalculate_factorial(void)
{
    fact.resize(MAXN);
    inv.resize(MAXN);
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    inv[MAXN - 1] = calc_power(fact[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

ll choose(int n, int k)
{
    assert(n >= k);

    ll nom = fact[n];
    ll den = inv[k] * inv[n - k] % MOD;

    return nom * den  % MOD;
}

int dfs(int node, int par)
{
    subtree_size[node] = 1;

    vector<int> kidsizes;
    for (auto kid : kids[node]) {
        if (kid != par) {
            int res = dfs(kid, node);
            kidsizes.pb(res);
            subtree_size[node] += res;
        }
    }

    if (V == 1) {
        // Only interested in wether it is possible to create the tree
        sort(kidsizes.begin(), kidsizes.end());
        int s = 1;
        for (int i = 0; i < kidsizes.size(); i++) {
            if (s < kidsizes[i]) {
                creatable = false;
            }
            s += kidsizes[i];
        }

        return subtree_size[node];
    }

    int M = kids[node].size();
    vector<ll> dp;
    vector<int> tot_size;
    dp.assign(1 << M, 0);
    tot_size.resize(1 << M);

    dp[0] = 1;
    tot_size[0] = 1;
    for (int s = 0; s < (1 << M); s++) {
        for (int i = 0; i < M; i++) {
            if (CHECK_BIT(s, i)) {
                continue;
            }
            int kid = kids[node][i];
            if (subtree_size[kid] > tot_size[s]) {
                continue;
            }

            // Add this kid in the subtree. Make sure the LAST connection
            // is uniting this kid to the root to ensure distinctness.

            // First calculate one possible combination of both
            ll ord = ways[kid] * dp[s] % MOD;
            // Then weave them together
            ll res = ord * choose(tot_size[s] - 1 + subtree_size[kid] - 1, subtree_size[kid] - 1) % MOD;

            dp[s ^ (1 << i)] = (dp[s ^ (1 << i)] + res) % MOD;
            tot_size[s ^ (1 << i)] = tot_size[s] + subtree_size[kid];
        }
    }

    ways[node] = dp[(1 << M) - 1];
    return subtree_size[node];
}

void clear_testcase(void)
{
    kids.clear();
    ways.clear();
    subtree_size.clear();
    par.clear();
    creatable = true;
}

void solve(void)
{
    clear_testcase();

    scanf("%d", &N);

    kids.resize(N);
    par.assign(N, -1);
    ways.resize(N);
    subtree_size.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, p;
        scanf("%d %d", &u, &p);
        u--; p--;

        kids[p].pb(u);
        par[u] = p;
    }

    int root = -1;
    for (int i = 0; i < N; i++) {
        if (par[i] == -1) {
            root = i;
        }
    }

    dfs(root, -1);

    if (V == 1) {
        if (creatable) {
            printf("1\n");
        }
        else {
            printf("0\n");
        }
    }
    else {
        printf("%lld\n", ways[root]);
    }
}

int main(void)
{
    freopen("prettytree.in", "r", stdin);
    freopen("prettytree.out", "w", stdout);

    scanf("%d %d", &T, &V);

    precalculate_factorial();

    while (T--) {
        solve();
    }

    return 0;
}