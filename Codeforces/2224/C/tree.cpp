#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int N, Q;
vector<vector<pi>> kids;
vector<int> p;
vector<ll> queries;

vector<int> primes;
vector<int> small;
vector<vector<int>> cnt;

int dfs(int node, ll a, ll b) {
    ll cur = kids[node].size();
}

void solve(void) {
    scanf("%d %d", &N, &Q);

    kids.assign(N, vector<pi>());
    p.resize(N);
    queries.resize(Q);

    for (int i = 1; i < N; i++) {
        scanf("%d", &p[i]);
        p[i]--;
    }
    for (int i = 1; i < N; i++) {
        int w;
        scanf("%d", &w);
        kids[p[i]].pb({i, w});
    }

    for (int i = 0; i < Q; i++) {
        scanf("%d", &queries[i]);
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}