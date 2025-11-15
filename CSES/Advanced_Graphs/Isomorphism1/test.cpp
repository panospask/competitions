#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int B2 = 1e6 + 3;
const int B1 = 1e6 + 19;
const int M1 = 1e9 + 7;
const int M2 = 998244353;

int N;
vector<vector<int>> adj_list;
vector<int> dep;
vector<map<ll, int>> category;

vector<ll> c;

int ans = 0;

int hashstr(vector<int>& v, const int& B, const int& M) {
    ll h = 0;
    for (int i = 0; i < v.size(); i++) {
        h = (h * B + v[i] + 1) % M;
    }

    return h;
}

ll result(vector<int>& v) {
    return (ll)INT_MAX * hashstr(v, B1, M1) + hashstr(v, B2,M2);
}

void dfs(int node, int par) {
    dep[node] = (par == -1 ? 0 : dep[par] + 1);
    
    vector<int> kids;
    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            dfs(neigh, node);
            kids.push_back(category[dep[neigh]][c[neigh]]);
        }
    }
    sort(kids.begin(), kids.end());

    c[node] = result(kids);
    if (category[dep[node]].count(c[node]) == 0) {
        category[dep[node]][c[node]] = category[dep[node]].size();
    }
}

void dfs2(int node, int par) {
    ans++;

    map<ll, int> cnt;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        cnt[c[neigh]]++;
    }
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        if (cnt[c[neigh]] == 1) {
            dfs2(neigh, node);
        }
    }
}

void solve(void) {
    scanf("%d", &N);
    
    adj_list.assign(2 * N + 1, vector<int>());
    c.assign(2 * N + 1, 0);
    category.clear();
    category.assign(2 * N + 1, map<ll, int>());
    dep.assign(2 * N + 1, 0);
    
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[N + u].push_back(N + v);
        adj_list[N + v].push_back(N + u);
    }

    adj_list[0].push_back(2 * N);
    adj_list[N].push_back(2 * N);
    adj_list[2 * N] = {0, N};

    ans =0;
    dfs(2 * N, -1);
    dfs2(2 * N, -1);

    if (ans == 1) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}