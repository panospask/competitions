#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, ll> pi;

const int MAXLOG = 20;
const ll INF = (ll)1e18 + 1;

int N;
ll L;
vector<vector<pi>> adj_list;
vector<pi> ancestor[MAXLOG];
vector<int> ans;
vector<int> remove_after;

void dfs(int node)
{
    for (auto [neigh, w] : adj_list[node])
        if (neigh != ancestor[0][node].f) {
            ancestor[0][neigh] = mp(node, w);
            dfs(neigh);
        }
}

void calculate_ancestors(void)
{
    for (int up = 1; up < MAXLOG; up++) {
        ancestor[up].resize(N);
        for (int i = 0; i < N; i++) {
            int u = ancestor[up - 1][i].f;

            ancestor[up][i].f = ancestor[up - 1][u].f;
            ancestor[up][i].s = ancestor[up - 1][i].s + ancestor[up - 1][u].s;
        }
    }
}

int calc_ans(int node)
{
    ans[node] = 1;
    for (auto [neigh, w] : adj_list[node])
        if (neigh != ancestor[0][node].f)
            ans[node] += calc_ans(neigh);

    return ans[node] - remove_after[node];
}

int main(void)
{
    freopen("runaway.in", "r", stdin);
    freopen("runaway.out", "w", stdout);

    scanf("%d %lld", &N, &L);

    adj_list.resize(N);
    ans.resize(N);
    ancestor[0].resize(N);
    remove_after.assign(N, 0);

    for (int i = 1; i <= N - 1; i++) {
        int v;
        ll w;
        scanf("%d %lld", &v, &w);
        v--;

        adj_list[i].pb(mp(v, w));
        adj_list[v].pb(mp(i, w));
    }

    ancestor[0][0] = mp(0, 0);
    dfs(0);

    calculate_ancestors();

    for (int i = 0; i < N; i++) {
        ll rem = L;
        int v = i;
        for (int up = MAXLOG - 1; up >= 0; up--) {
            if (ancestor[up][v].s <= rem) {
                rem -= ancestor[up][v].s;
                v = ancestor[up][v].f;
            }
        }

        remove_after[v]++;
    }

    calc_ans(0);

    for (int i = 0; i < N; i++)
        printf("%d\n", ans[i]);

    return 0;
}