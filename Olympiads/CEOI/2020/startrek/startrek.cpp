#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int MOD = 1e9 + 7;

int N;
ll D;
vector<vector<int>> adj_list;

// wins[i]: True iff node i is a winning state (as a root)
vector<bool> win;

// Same as win[i] but considering only the nodes in the subtree of i
vector<bool> sub_win;

/* critical[i]:
 * Count of nodes such that if i is the root of the tree and 
 * we place a portal at these nodes, the state of i will change.
 * 
 * They are the L-state nodes that can reach i via a path in which
 * every W-state node has only one L-state child
 */
vector<int> critical;

/* sub_crit[i]:
 * Similar to critical[i] but considering only the subtree of i when
 * the root is 0
 */
vector<int> sub_crit;

/* l_crit[i]:
 * Similar to critical[i] but assuming i is an L-state. 
 */
vector<int> l_crit;

ll calc_power(ll a, ll b)
{
    a = (a % MOD + MOD) % MOD;

    ll c = 1;

    while (b) {
        if (b & 1) {
            c = c * a % MOD;
        }

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

void dfs(int node, int par)
{
    sub_win[node] = false;
    sub_crit[node] = 0;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);

        if (!sub_win[neigh] && !sub_win[node]) {
            // First kid of this node that is losing

            sub_win[node] = true;
            sub_crit[node] = sub_crit[neigh];
        }
        else if (!sub_win[neigh] && sub_win[node]) {
            // This node has at least 2 kids that lose, even if one is blocked (by portal)
            // the captain can choose to go to the other kid
            sub_crit[node] = 0;
        }
        else if (sub_win[neigh] && !sub_win[node]) {
            sub_crit[node] += sub_crit[neigh];
        }
    }

    if (!sub_win[node]) {
        sub_crit[node]++;
    }
}

// Recalculate win and critical by also accounting for the nodes outside the subtree of node
void propagate(int node, int par)
{

    win[node] = false;
    critical[node] = 0;
    l_crit[node] = 1;

    int losekids = 0;
    int losetot = 0;

    // Variable used for the case that there is only one path to victory for this node
    // Identify the path
    int onlypath = -1;

    for (auto neigh : adj_list[node]) {
        if (!sub_win[neigh]) {
            if (!win[node]) {
                // The first neighbour of this node that is losing

                win[node] = true;
                critical[node] = sub_crit[neigh];
                onlypath = neigh;
            }
            else {
                // This node has at least 2 losing neighbours. Even if one is blocked by portal
                // the captain can choose the other one

                onlypath = -1;
                critical[node] = 0;
            }

            losekids++;
            losetot += sub_crit[neigh];
        }
        else {
            l_crit[node] += sub_crit[neigh];
        }
    }

    if (!win[node]) {
        critical[node] = l_crit[node];
    }

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        if (win[node]) {
            if (onlypath == neigh) {
                sub_win[node] = false;
                sub_crit[node] = l_crit[node];
            }
            else {
                sub_win[node] = win[node];
                sub_crit[node] = critical[node];

                if (losekids == 2 && !sub_win[neigh]) {
                    sub_crit[node] = losetot - sub_crit[neigh];
                }
            }
        }
        else {
            sub_win[node] = false;
            sub_crit[node] = critical[node] - sub_crit[neigh];
        }

        propagate(neigh, node);
    }
}

ll calc_inverse(ll a)
{
    return calc_power(a, MOD - 2);
}

void read_input(void)
{
    scanf("%d %lld", &N, &D);

    adj_list.resize(N);
    critical.resize(N);
    win.resize(N);
    sub_win.resize(N);
    sub_crit.resize(N);
    l_crit.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }
}

void TEST(void)
{
    for (int i = 0; i < N; i++) {
        dfs(i, i);
        assert(sub_crit[i] == critical[i]);
    }
}

int main(void)
{
    read_input();

    dfs(0, 0);
    propagate(0, 0);

    int wincnt = 0, losecnt = 0;
    ll wincrit = 0, losecrit = 0;

    for (int i = 0; i < N; i++) {
        if (win[i]) {
            wincnt++;
            wincrit += critical[i];
        }
        else {
            losecnt++;
            losecrit += critical[i];
        }
    }

    int E = wincrit - losecrit;
    ll res = losecnt * (calc_power(N, 2 * D) - calc_power(E, D)) % MOD * calc_inverse((ll)N * N % MOD - E) % MOD;
    res = (res % MOD + MOD) % MOD;

    if (win[0]) {
        res = calc_power(N, 2 * D) - critical[0] * res % MOD;
    }
    else {
        res = critical[0] * res % MOD;
    }

    res = (res % MOD + MOD) % MOD;

    printf("%lld\n", res);

    return 0;
}