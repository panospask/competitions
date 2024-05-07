#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N, M;

vector<vector<int>> adj_list;
vector<bool> visited;
vector<int> dep;
vector<int> par;
vector<int> cnt;
vector<int> ans;
vector<int> tops;
bool found = false, rv = false;

bool locate_cycle(int node, int l)
{
    for (auto neigh : adj_list[node]) {
        if (neigh == par[node]) {
            continue;
        }

        if (dep[neigh] < dep[l]) {
            // Found the target cycle
            tops.pb(neigh);

            vector<int> v;
            for (int i = node; i != l; i = par[i]) {
                v.pb(i);
            }
            if (rv) {
                reverse(v.begin(), v.end());
            }

            for (int i = 0; i < v.size(); i++) {
                ans.pb(v[i]);
            }

            return true;
        }
        else if (par[neigh] == node) {
            if (locate_cycle(neigh, l)) {
                return true;
            }
        }
    }

    return false;
}

int dfs(int node, int p)
{
    visited[node] = true;
    par[node] = p;

    for (auto neigh : adj_list[node]) {
        if (neigh == par[node]) {
            continue;
        }

        if (visited[neigh] && dep[neigh] < dep[node]) {
            if ((dep[node] - dep[neigh]) % 2 != 0) {
                // Even cycle, make answer
                found = true;
                for (int i = node; i != neigh; i = par[i]) {
                    ans.pb(i);
                }
                ans.pb(neigh);
            }

            // Back edge
            cnt[node]++;
            cnt[neigh]--;
        }
        else if (!visited[neigh]) {
            // Forward edge
            dep[neigh] = dep[node] + 1;
            cnt[node] += dfs(neigh, node);
        }
    }

    if (cnt[node] >= 2 && !found) {
        // Found an even cycle as a composition of 2 odd cycles in the dfs tree
        found = true;

        // We have to locate and concatenate the two cycles
        int rem = 2;
        for (auto neigh : adj_list[node]) {
            if (rem == 1 && (ans.empty() || ans.back() != node)) {
                rv = true;
                ans.pb(node);
            }
            else if (rem == 0) {
                break;
            }

            if (par[neigh] == node && rem) {
                int res = locate_cycle(neigh, node);
                if (res) {
                    rem--;
                }
            }
            else if (neigh != par[node] && dep[neigh] < dep[node]) {
                tops.pb(neigh);
                rem--;
            }
        }

        // just have to unite tops[0], tops[1]
        if (dep[tops[0]] > dep[tops[1]]) {
            swap(tops[0], tops[1]);
            reverse(ans.begin(), ans.end());
        }

        for (int i = tops[1]; i != tops[0]; i = par[i]) {
            ans.pb(i);
        }
        ans.pb(tops[0]);
    }

    return cnt[node];
}

void solve(void)
{
    scanf("%d %d", &N, &M);

    tops.clear();
    ans.clear();
    adj_list.assign(N, vector<int>());
    cnt.assign(N, 0);
    par.resize(N);
    dep.resize(N);
    visited.assign(N, false);
    found = false, rv = false;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i] && !found) {
            dep[i] = 0;
            dfs(i, -1);
        }
    }

    if (found) {
        printf("cycle %d", (int)ans.size());
        for (int i = 0; i < ans.size(); i++) {
            printf(" %d", ans[i] + 1);
        }
    }
    else {
        printf("none");
    }
    printf("\n");
}

int main(void)
{
    freopen("evencycle.in", "r", stdin);
    freopen("evencycle.out", "w", stdout);

    int T;
    scanf("%d", &T);

    while (T--) {
        solve();
    }

    return 0;
}