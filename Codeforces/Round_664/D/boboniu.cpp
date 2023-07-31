#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll ans = 0;

int N;
vector<vector<int>> adj_list;
vector<ll> increasing;
vector<ll> decreasing;
vector<int> h;
vector<int> t;

void dfs(int node, int par)
{
    vector<int> heights;

    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            heights.push_back(neigh);
            dfs(neigh, node);
        }
    }

    int l = 0;
    int r = heights.size() - 1;
    ll res = 0;
    while (r > l && h[heights[l]] <= h[node] && h[heights[r]] >= h[node]) {
        res += increasing[l] + t[node] + decreasing[r];
        r--;
        l++;
    }
    ans += (ll)(r - l + 1) * t[node];
}

void solve(void)
{
    ans = 0;
    adj_list.clear();

    scanf("%d", &N);

    adj_list.resize(N);
    h.resize(N);
    t.resize(N);

    for (int i = 0; i < N; i++)
        scanf("%d", &t[i]);
    for (int i = 0; i < N; i++)
        scanf("%d", &h[i]);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(0, -1);

    ll sum = 0;
    for (int i = 0; i < N; i++)
        sum += t[i];
    sum += t[0];
    sum += t[5] + t[6] + t[8];

    cerr << sum << endl;

    printf("%lld\n", ans);
}

int main(void)
{
    int t;
    t = 1;
    while (t--)
        solve();

    return 0;
}