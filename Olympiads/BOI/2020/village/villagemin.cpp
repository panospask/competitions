#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

int n;
ll ans = 0;
vector<int> lives_at;
vector<vector<int>> adj_list;

void dfs(int node, int par)
{
    for (auto neigh : adj_list[node])
        if (neigh != par)
            dfs(neigh, node);

    if (lives_at[node] == node) {
        if (par != -1) {
            swap(lives_at[node], lives_at[par]);
            ans += 2;
        }
        else {
            swap(lives_at[node], lives_at[adj_list[node].front()]);
            ans += 2;
        }
    }
}

int main(void)
{
    scanf("%d", &n);

    adj_list.resize(n);
    lives_at.resize(n);
    for (int i = 0; i < n; i++)
        lives_at[i] = i;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    dfs(0, -1);

    vector<int> v(n);
    for (int i = 0; i < n; i++)
        v[lives_at[i]] = i;

    printf("%lld\n", ans);
    for (auto vil : v)
        printf("%d ", vil + 1);
    printf("\n");

    return 0;
}