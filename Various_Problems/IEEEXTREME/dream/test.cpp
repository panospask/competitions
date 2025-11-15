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

int main(void) {
    scanf("%d", &N);
    
    adj_list.assign(N, vector<int>());
    c.assign(N, 0);
    category.clear();
    category.assign(N, map<ll, int>());
    dep.assign(N, 0);
    
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    ans = 0;
    vector<map<ll, int>> cnt(N);
    dfs(0, -1);
    for (int i = 0; i < N; i++) {
        cnt[dep[i]][c[i]]++;
    }
    for (int d = 0; d < N; d++) {
        for (auto [h, v] : cnt[d]) {
            if (v == 1) {
                ans++;
            }
        }
    }


    printf("%d\n", ans);
}