#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

int N;
vector<vector<int>> adj_list;
vector<int> l, r;

//value[i]: The optimal value for i when assuming that par is the actual parent
vector<int> value;
// How much the answer is increased by for i when assuming that par is the actual parent
vector<ll> ans;

ll answer = 0;

int choose_value(int m, int node)
{
    if (m < l[node]) {
        return l[node];
    }
    else if (m > r[node]) {
        return r[node];
    }
    else {
        return m;
    }
}

void dfs(int node, int par)
{
    ans[node] = 0;

    int maxkid = -1;
    for (auto kid : adj_list[node]) {
        if (kid == par) {
            continue;
        }

        dfs(kid, node);
        ans[node] += ans[kid];
        maxkid = max(maxkid, value[kid]);
    }

    value[node] = choose_value(maxkid, node);

    for (auto kid : adj_list[node]) {
        if (kid == par) {
            continue;
        }

        if (value[kid] > value[node]) {
            ans[node] += value[kid] - value[node];
        }
    }
}

void reroot(int node, int par, int par_value, ll par_answer)
{
    // Assume current node is root
    int maxkids[2] = {par_value, -1};

    ll kidcosts = 0;
    for (auto kid : adj_list[node]) {
        if (kid == par) {
            continue;
        }

        kidcosts += ans[kid];
        int v = value[kid];
        if (maxkids[0] < v) {
            swap(maxkids[0], v);
        }
        if (maxkids[1] < v) {
            swap(maxkids[1], v);
        }
    }
    int cur_values[2] = {choose_value(maxkids[0], node), choose_value(maxkids[1], node)};
    
    // How much would it cost to put the current node as root
    ll total[2] = {kidcosts + par_answer, kidcosts + par_answer};
    for (auto kid : adj_list[node]) {
        if (kid == par) {
            continue;
        }

        for (int t = 0; t < 2; t++) {
            if (value[kid] > cur_values[t]) {
                total[t] += value[kid] - cur_values[t];
            }
        }
    }
    // Don't forget that par is now a child
    for (int t = 0; t < 2; t++) {
            if (par_value > cur_values[t]) {
                total[t] += par_value - cur_values[t];
            }
        }
    answer = min(answer, total[0] + cur_values[0]);

    for (auto kid : adj_list[node]) {
        if (kid == par) {
            continue;
        }

        int idx = 0;
        if (value[kid] == maxkids[0]) {
            idx = 1;
        }

        total[idx] -= max(value[kid] - cur_values[idx], 0);
        reroot(kid, node, cur_values[idx], total[idx]);
        total[idx] += max(value[kid] - cur_values[idx], 0);
    }
}

void solve(void)
{
    scanf("%d", &N);
    adj_list.assign(N, vector<int>());
    l.resize(N);
    r.resize(N);
    value.resize(N);
    ans.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &l[i], &r[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    answer = LLONG_MAX;
    dfs(0, -1);
    reroot(0, -1, -1, 0);

    printf("%lld\n", answer);
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