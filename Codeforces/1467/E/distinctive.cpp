#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<int> A;
vector<vector<int>> adj_list;
vector<int> vals;

vector<int> cnt;
// Which adjacents (including parent) lead to a node of same color?
// If thre is only one, we exclude it from failure, otherwise all go 
vector<vector<int>> similar;

vector<bool> failed;

bool isfail(int node, int neigh) {
    return (similar[node].size() >= 2 || (similar[node].size() == 1 && similar[node].front() != neigh));
}

void dfs(int node, int par) {
    if (cnt[A[node]]) {
        // The other node will either get the update from child
        // or from the count fact in the reverse order
        similar[node].pb(par);
    }

    cnt[A[node]]++;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        int x = cnt[A[node]];
        dfs(neigh, node);
        if (cnt[A[node]] != x) {
            similar[node].pb(neigh);
        }
    }
}

bool failUp(int node, int par) {
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        int res = failUp(neigh, node);
        if (res) {
            // res true means that all (but neigh) should die
            if (similar[node].size() == 0 || similar[node].front() != neigh) {
                similar[node].pb(neigh);
            }
        }
    }

    if (isfail(node, par)) {
        return true;
    }
    else {
        return false;
    }
}

// must is true if the command comes from parent
void failDown(int node, int par) {
    if (similar[node].size() >= 1) {
        failed[node] = true;
    }
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        if (isfail(node, neigh)) {
            if (similar[neigh].size() == 0 || (similar[neigh].front() != node)) {
                similar[neigh].pb(node);
            }
        }
        failDown(neigh, node);
    }
}

int main(void) {
    scanf("%d", &N);

    A.resize(N);
    adj_list.resize(N);
    failed.assign(N, false);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        vals.pb(A[i]);
    }
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    for (int i = 0; i < N; i++) {
        int p = lower_bound(vals.begin(), vals.end(), A[i]) - vals.begin();
        A[i] = p;
    }

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    similar.assign(N, vector<int>());
    cnt.assign(vals.size(), 0);
    dfs(0, -1);
    for (int i = 0; i < N; i++) {
        reverse(adj_list[i].begin(), adj_list[i].end());
    }
    cnt.assign(vals.size(), 0);
    dfs(0, -1);

    for (int i = 0; i < N; i++) {
        sort(similar[i].begin(), similar[i].end());
        similar[i].resize(unique(similar[i].begin(), similar[i].end()) - similar[i].begin());
    }

    failUp(0, -1);
    failDown(0, -1);

    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans += !failed[i];
    }

    printf("%d\n", ans);
}