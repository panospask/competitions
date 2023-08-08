#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

int N;
vector<vector<int>> adj_list;
vector<int> sz;

int dom_v;
ll res;
vector<ll> ans;
vector<int> col;
vector<int> cnt;

int counter = 0;
vector<int> tin;
vector<int> tout;
vector<int> trav;

void dfs(int node, int par, bool isheavy)
{
    int BigKid = -1;
    int BigV = 0;
    for (auto kid : adj_list[node]) {
        if (kid != par) {
            if (sz[kid] > BigV) {
                BigKid = kid;
                BigV = sz[kid];
            }
        }
    }

    for (auto kid : adj_list[node])
        if (kid != par && kid != BigKid)
            dfs(kid, node, false);

    int orig_dom = dom_v;
    ll or_res = res;

    if (BigKid != -1)
        dfs(BigKid, node, true);

    cnt[col[node]]++;
    if (cnt[col[node]] > dom_v) {
        dom_v = cnt[col[node]];
        res = 0;
    }
    if (cnt[col[node]] == dom_v) {
        res += col[node];
    }

    for (auto kid : adj_list[node]) {
        if (kid == par || kid == BigKid)
            continue;

        for (int t = tin[kid]; t < tout[kid]; t++) {
            int c = col[trav[t]];
            cnt[c]++;

            if (cnt[c] > dom_v) {
                dom_v = cnt[c];
                res = 0;
            }
            if (cnt[c] == dom_v) {
                res += c;
            }
        }
    }

    ans[node] = res;

    if (!isheavy) {
        dom_v = orig_dom;
        res = or_res;

        for (int t = tin[node]; t < tout[node]; t++) {
            int c = col[trav[t]];
            cnt[c]--;
        }
    }
}

void init(int node, int par)
{
    tin[node] = counter++;
    trav[tin[node]] = node;

    sz[node] = 1;
    for (auto kid : adj_list[node])
        if (kid != par) {
            init(kid, node);
            sz[node] += sz[kid];
        }

    tout[node] = counter;
}

int main(void)
{
    scanf("%d", &N);

    adj_list.resize(N);
    tin.resize(N);
    tout.resize(N);
    trav.resize(N);
    col.resize(N);
    ans.resize(N);
    sz.resize(N);

    cnt.resize(N + 1);

    for (int i = 0; i < N; i++)
        scanf("%d", &col[i]);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    init(0, -1);
    dfs(0, -1, true);

    for (int i = 0; i < N; i++)
        printf("%lld ", ans[i]);
    printf("\n");

    return 0;
}