#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const ll INF = 1e18;

const int MAXN = 5000;

// A tree can be made harmonious by assigning 2 to each node
const int MAXCOST = 2 * MAXN;

int N;
vector<int> a;
vector<vector<int>> adj_list;

/* dp[node][v]:
 * Maximum cost of making a tree harmonious such that the value at node
 * is NOT comprime with v.
 */
vector<vector<ll>> dp;

// Primes and prime decomposition of each number
vector<vector<int>> prime_decomposition;

void makemin(ll& a, ll& b)
{
    if (a > b) {
        a = b;
    }
}

void dfs(int node, int par)
{
    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            dfs(neigh, node);
        }        
    }

    for (int v = 2; v <= MAXCOST; v++) {
        dp[node][v] = 0;
        for (auto neigh : adj_list[node]) {
            if (neigh != par) {
                dp[node][v] += dp[neigh][v];
            }
        }

        if (v != a[node]) {
            dp[node][v] += v;
        }
    }

    // Propagate the results
    for (int v = MAXCOST; v >= 2; v--) {
        for (auto p : prime_decomposition[v]) {
            makemin(dp[node][v / p], dp[node][v]);
        }
    }
    for (int v = 2; v <= MAXCOST; v++) {
        for (auto p : prime_decomposition[v]) {
            makemin(dp[node][v], dp[node][v / p]);
        }
    }
}

void sieve(void)
{    
    prime_decomposition.resize(MAXCOST + 1);

    for (int i = 2; i <= MAXCOST; i++) {
        if (prime_decomposition[i].empty()) {
            for (int j = 2 * i; j <= MAXCOST; j += i) {
                prime_decomposition[j].push_back(i);
            }
        }
    }
}

int main(void)
{
    sieve();

    scanf("%d", &N);

    a.resize(N);
    adj_list.resize(N);
    dp.assign(N, vector<ll>(MAXCOST + 1, INF));

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(0, 0);

    ll ans = INF;
    for (int i = 2; i <= MAXCOST; i++) {
        makemin(ans, dp[0][i]);
    }

    printf("%lld\n", ans);
}