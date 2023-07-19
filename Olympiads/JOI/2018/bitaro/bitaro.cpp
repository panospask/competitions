#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

int N, M, Q;
vector<vector<pi>> dist;
vector<vector<int>> adj_list;
int BLOCK_SIZE;
vector<bool> ban;
vector<int> curbanned;
vector<int> dp;
vector<bool> use;

int find(int i, vector<int>& v)
{
    int p = lower_bound(v.begin(), v.end(), i) - v.begin();

    if (p < v.size() && v[p] == i)
        return true;
    else
        return false;
}

int naive_dp(int dest, vector<bool>& banned)
{
    dp.assign(N, -1);

    for (int i = 0; i < N; i++) {
        if (!banned[i]) {
            dp[i] = max(dp[i], 0);
        }
        if (dp[i] == -1) {
            continue;
        }

        for (auto v : adj_list[i])
            dp[v] = max(dp[v], dp[i] + 1);
    }

    return dp[dest];
}

int find_from_precalculate(int c, vector<bool>& banned)
{
    int ans = -1;
    for (auto v : dist[c]) {

        if (!banned[v.first])
            ans = max(ans, v.second);
    }

    return ans;
}

void merge(vector<pi>& a, vector<pi>& b)
{
    vector<pi> c;

    int p_a = 0;
    int p_b = 0;
    int ins = 0;

    while (p_a < a.size() && p_b < b.size() && ins < BLOCK_SIZE) {
        if (a[p_a].second >= b[p_b].second + 1) {
            if (!use[a[p_a].first]) {
                use[a[p_a].first] = true;
                c.push_back(a[p_a]);
                ins++;
            }
            p_a++;
        }
        else {
            if (!use[b[p_b].first]) {
                use[b[p_b].first] = true;
                ins++;
                c.push_back(b[p_b]);
                c.back().second++;
            }
            p_b++;
        }
    }

    while (p_a < a.size() && ins < BLOCK_SIZE) {
        if (!use[a[p_a].first]) {
            use[a[p_a].first] = true;
            c.push_back(a[p_a]);
            ins++;
        }
        p_a++;
    }
    while (p_b < b.size() && ins < BLOCK_SIZE) {
        if (!use[b[p_b].first]) {
            use[b[p_b].first] = true;
            ins++;
            c.push_back(b[p_b]);
            c.back().second++;
        }
        p_b++;
    }


    a = c;
    for (auto v : a)
        use[v.first] = false;
}

int main(void)
{
    scanf("%d %d %d", &N, &M, &Q);

    BLOCK_SIZE = ceil(sqrt(N));

    adj_list.resize(N);
    dist.resize(N);
    ban.resize(N);
    use.resize(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
    }

    // Precalculate best cities
    for (int i = 0; i < N; i++) {
        if (dist[i].size() < BLOCK_SIZE)
            dist[i].push_back({i, 0});

        for (auto neigh : adj_list[i]) {
            merge(dist[neigh], dist[i]);
        }
    }


    for (int i = 0; i < Q; i++) {
        int T, Y;
        scanf("%d %d", &T, &Y);
        T--;

        for (int j = 0; j < Y; j++) {
            int c;
            scanf("%d", &c);
            c--;

            curbanned.push_back(c);
            ban[c] = true;
        }
        sort(curbanned.begin(), curbanned.end());

        int ans = 0;
        if (Y >= BLOCK_SIZE)
            ans = naive_dp(T, ban);
        else
            ans = find_from_precalculate(T, ban);

        while (curbanned.size()) {
            ban[curbanned.back()] = false;
            curbanned.pop_back();
        }

        printf("%d\n", ans);
    }

    return 0;
}