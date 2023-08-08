#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

int N;
vector<vector<int>> adj_list;
unordered_map<int, int> compress;
vector<int> force;
vector<int> sz;
vector<int> p;
vector<int> ans;
vector<int> all;
vector<int> tot;

vector<int> cnt;
vector<int> ancestor_count;
vector<int> tin;
vector<int> tout;
vector<int> trav;
int counter;

void dfs(int node, bool is_heavy)
{
    int BigKid = -1;
    int BigV = 0;

    for (auto kid : adj_list[node]) {
        if (sz[kid] > BigV) {
            BigV = sz[kid];
            BigKid = kid;
        }
    }

    ancestor_count[compress[p[node]]]++;
    for (auto kid : adj_list[node]) {
        if (kid != BigKid)
            dfs(kid, false);
    }
    if (BigKid != -1)
        dfs(BigKid, true);
    ancestor_count[compress[p[node]]]--;

    cnt[compress[p[node]]]++;
    for (auto kid : adj_list[node]) {
        if (kid == BigKid)
            continue;

        for (int t = tin[kid]; t < tout[kid]; t++) {
            cnt[compress[p[trav[t]]]]++;
        }
    }

    ans[node] -= ancestor_count[compress[p[node]]];
    ans[node] -= cnt[compress[p[node]]];

    if (!is_heavy) {
        for (int t = tin[node]; t < tout[node]; t++)
            cnt[compress[p[trav[t]]]]--;
    }
}

void init(int node)
{
    tin[node] = counter++;
    trav[tin[node]] = node;

    p[node] = force[node];
    sz[node] = 1;

    for (auto kid : adj_list[node]) {
        init(kid);
        p[node] += p[kid];
        sz[node] += sz[kid];
    }

    all.pb(p[node]);
    tout[node] = counter;
}

int main(void)
{
    freopen("conflicts.in", "r", stdin);
    freopen("conflicts.out", "w", stdout);

    scanf("%d", &N);

    ans.resize(N);
    tin.resize(N);
    tout.resize(N);
    adj_list.resize(N);
    p.resize(N);
    sz.resize(N);
    force.resize(N);
    trav.resize(N);

    scanf("%d", &force[0]);
    for (int i = 1; i < N; i++) {
        int par;
        scanf("%d %d", &par, &force[i]);
        adj_list[--par].pb(i);
    }

    init(0);

    sort(all.begin(), all.end());
    all.resize(unique(all.begin(), all.end()) - all.begin());

    tot.resize(all.size());
    ancestor_count.resize(all.size());
    cnt.resize(all.size());
    for (int i = 0; i < all.size(); i++)
        compress[all[i]] = i;

    for (int i = 0; i < N; i++) {
        tot[compress[p[i]]]++;
    }
    for (int i = 0; i < N; i++) {
        ans[i] = tot[compress[p[i]]];
    }

    dfs(0, true);

    for (int i = 0; i < N; i++)
        printf("%d\n", ans[i]);

    return 0;
}