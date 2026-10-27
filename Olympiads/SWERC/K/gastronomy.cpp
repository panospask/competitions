#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int MAXN = 500005;

typedef long long ll;

int N;
vector<int> p;
vector<vector<int>> adj_list;
vector<int> subtree;

// dp[node]: Incl. this node, how many paths are formed to adj_list?
vector<ll> dp;

vector<int> cnt;

int centroid = 0;

void dfs(int node, int par) {
    subtree[node] = 1;
    dp[node] = 0;

    for (auto kid : adj_list[node]) {
        if (kid == par) {
            continue;
        }

        dfs(kid, node);
        dp[node] += dp[kid];
        subtree[node] += subtree[kid];
    }
    dp[node] += subtree[node];

    if (N - subtree[node] <= N / 2) {
        bool good = true;
        for (auto kid : adj_list[node]) {
            if (kid != par && subtree[kid] > N / 2) {
                good = false;
            }
        }
        if (good) {
            centroid = node;
        }
    }
}

int main(void) {
    scanf("%d", &N);

    p.resize(N);
    subtree.resize(N);
    adj_list.resize(N);
    dp.resize(N);

    for (int i = 1; i < N; i++) {
        scanf("%d", &p[i]);
        p[i]--;
        adj_list[p[i]].pb(i);
        adj_list[i].pb(p[i]);
    }

    dfs(0, -1);
    int tmp_var = centroid;
    dfs(centroid, -1);
    centroid = tmp_var;

    cnt.assign(N, 0);
    for (auto neigh : adj_list[centroid]) {
        cnt[subtree[neigh]]++;
    }
    for (int v = 0; v <= N / 2; v++) {
        int x = cnt[v] / 2;
        cnt[v] %= 2;

        if (x && cnt[v] == 0) {
            cnt[v] += 2;
            x--;
        }

        if (2 * v <= N / 2) {
            cnt[2 * v] += x;
        }
    }

    bitset<MAXN> possible;
    possible.set(0);
    for (int v = 1; v <= N / 2; v++) {
        for (int x = 0; x < cnt[v]; x++) {
            possible = (possible | (possible << v));
        }
    }

    ll ans = 0;
    ans = dp[centroid];
    for (int v = (N - 1) / 2; v >= 0; v--) {
        if (possible.test(v)) {
            ans += (ll)v * (ll)(N - 1 - v);
            break;
        }
    }

    printf("%lld\n", ans);
    return 0;
}