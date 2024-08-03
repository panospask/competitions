#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define makemax(a, b) ((a) = max((a), (b)))

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const ll INF = 1e15;
const int MAXN = 151;

int N;
vector<short int> adj_list[MAXN];
int a[MAXN];
vector<pi> pairs;

/* dist[i][j]:
 * Unweighted distance between i and j
 */
short int dist[MAXN][MAXN];

/* subtree[i][j]:
 * If i is root, what is the subtree size of j
 */
short int subtree[MAXN][MAXN];

/*dp[i][j][k][p1][p2]:
 * The longest path from i to j if we have used k operations so far
 * p1 and p2 are boolean variables indicating if we have placed the edges
 * (i, par[j][i]) and (j, par[i][j]) respectively 
 * 
 * When p1 or p2 are true, we can no longer move to kids of i and j.
 */
vector<vector<vector<vector<ll>>>> dp;
vector<vector<vector<vector<ll>>>> prv;

int K;
// prv[i][j][p1][false] is optimal, expand upon that
inline void process_state(int i, int j, bool p1)
{
    if (prv[i][j][p1][false] < 0) {
        return;
    }

    // How many operations can we perform on random(not important) nodes
    int remaining_operations = N - 1 - K - subtree[i][j];
    if (!p1) {
        remaining_operations -= subtree[j][i];
    }

    if (remaining_operations < 0) {
        return;
    }

    // Unite j with par[j]

    // Either stop there
    makemax(dp[i][j][p1][true], prv[i][j][p1][false] + a[K]);

    // Or find new target
    for (auto neigh : adj_list[j]) {
        if (dist[i][neigh] < dist[i][j]) {
            // Parent
            continue;
        }

        makemax(dp[i][neigh][p1][false], prv[i][j][p1][false] + a[K]);
    }
}

void dfs(int node, int par, int root)
{
    subtree[root][node] = 1;

    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            dist[root][neigh] = dist[root][node] + 1;
            dfs(neigh, node, root);
            subtree[root][node] += subtree[root][neigh];
        }
    }
}

inline void process_pair(int i, int j)
{
    for (int p1 = 0; p1 < 2; p1++) {
        for (int p2 = 0; p2 < 2; p2++) {
            prv[i][j][p1][p2] = prv[j][i][p2][p1] = max(prv[i][j][p1][p2], prv[j][i][p2][p1]);
            makemax(dp[i][j][p1][p2], prv[i][j][p1][p2]);
            makemax(dp[j][i][p2][p1], prv[j][i][p2][p1]);
        }
    }
    for (int p1 = 0; p1 < 2; p1++) {
            process_state(i, j, p1);
            process_state(j, i, p1);
    }
}

bool distancesort(const pi& a, const pi& b)
{
    return dist[a.first][a.second] < dist[b.first][b.second];
}

inline void clear_dp(void)
{
    dp.assign(N, vector<vector<vector<ll>>>(N, vector<vector<ll>>(2, vector<ll>(2, -INF))));
    prv.assign(N, vector<vector<vector<ll>>>(N, vector<vector<ll>>(2, vector<ll>(2, -INF))));

}

void solve(void)
{
    scanf("%d", &N);
    N++;

    clear_dp();
    pairs.clear();

    for (int i = 0; i < N - 1; i++) {
        scanf("%d", &a[i]);
        adj_list[i].clear();
    }
    adj_list[N - 1].clear();

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    for (int i = 0; i < N; i++) {
        dist[i][i] = 0;
        dfs(i, -1, i);
    }

    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            pairs.pb(mp(i, j));
        }
    }
    sort(pairs.begin(), pairs.end(), distancesort);

    // Initialize dp states
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            if (dist[i][j] == 0) {
                dp[i][j][true][true] = 0;
            }
            else if (dist[i][j] == 1) {
                dp[i][j][true][false] = 0;
            }
            else if (dist[i][j] == 2) {
                dp[i][j][false][false] = 0;
            }
        }
    }

    for (K = 0; K < N - 1; K++) {
        swap(dp, prv);
        // clear_dp();
        for (auto [i, j] : pairs) {
            process_pair(i, j);
        }
    }

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ans = max(ans, dp[i][j][true][true]);
        }
    }

    printf("%lld\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}