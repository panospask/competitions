#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct Upd {
    int time;
    int diff;
    int node;
};

int N, Q;
vector<vector<int>> adj_list;
// dp[u]: # Of different white pairs without including u itself
vector<ll> dp, sz;
vector<ll> tmp_sz;
vector<int> state, par;
vector<vector<pi>> updates;
vector<vector<int>> queries;
vector<int> lazy;
vector<ll> ans;

void initialize(int node, int p)
{
    par[node] = p;

    dp[node] = sz[node] = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh == par[node])
            continue;

        initialize(neigh, node);
        dp[node] += sz[node] * sz[neigh];
        sz[node] += sz[neigh];
    }

    sz[node] += state[node];
}

void process(int node)
{
    int update_cnt = updates[node].size();
    int id = -1;
    int different = !updates[node].empty();
    int init_sate = state[node];

    ll cur_ans = dp[node];
    ll cur_sz = sz[node] - state[node];
    tmp_sz[node] = sz[node];

    dp[node] = sz[node] = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh == par[node])
            continue;

        process(neigh);
        if (!updates[neigh].empty()) {
            different++;
            id = neigh;
            update_cnt += updates[neigh].size();
        }

        dp[node] += sz[node] * sz[neigh];
        sz[node] += sz[neigh];
    }

    state[node] = (update_cnt % 2) ^ state[node];
    sz[node] += state[node];

    if (different < 2 && queries[node].empty()) {
        // Add to lazy, no need to process all updates independently

        if (id != -1) {
            swap(updates[node], updates[id]);
            lazy[node] = lazy[id];
            if (init_sate)
                lazy[node]--;
            else
                lazy[node]++;
        }
        else {
            if (init_sate)
                lazy[node] = -1;
            else
                lazy[node] = 1;
        }

        return;
    }

    vector<Upd> all_updates;

    // Insert current node updates
    for (int i = 0; i < updates[node].size(); i++) {
        all_updates.push_back({updates[node][i].f, updates[node][i].s, node});
    }

    // Process normally
    if (init_sate)
        lazy[node] = -1;
    else
        lazy[node] = 1;
    for (auto neigh : adj_list[node]) {
        if (neigh == par[node] || updates[neigh].empty())
            continue;

        // Propagate the laziness
        for (int i = 0; i < updates[neigh].size(); i++) {
            updates[neigh][i].s += lazy[neigh] * (i % 2 ? -1 : 1);
        }

        // Merge updates[neigh] with all_updates
        vector<Upd> temp;
        int cur = 0;
        for (auto v : all_updates) {
            while (cur < updates[neigh].size() && updates[neigh][cur].f < v.time) {
                temp.push_back({updates[neigh][cur].f, updates[neigh][cur].s, neigh});
                cur++;
            }
            temp.push_back(v);
        }
        while (cur < updates[neigh].size()) {
            temp.push_back({updates[neigh][cur].f, updates[neigh][cur].s, neigh});
            cur++;
        }

        // No longer needed
        updates[neigh].clear();

        swap(temp, all_updates);
    }

    // Move updates to current node
    updates[node].resize(all_updates.size());
    for (int i = 0; i < all_updates.size(); i++)
        updates[node][i] = mp(all_updates[i].time, all_updates[i].diff);

    // Process queries
    int latest_upd = 0;
    int cur_state = init_sate;
    for (auto t : queries[node]) {
        while (latest_upd < all_updates.size() && all_updates[latest_upd].time < t) {
            int from = all_updates[latest_upd].node;

            cur_sz -= tmp_sz[from];
            cur_ans -= cur_sz * tmp_sz[from];

            tmp_sz[from] += all_updates[latest_upd].diff;
            cur_state = !cur_state;

            cur_ans += cur_sz * tmp_sz[from];
            cur_sz += tmp_sz[from];


            latest_upd++;
        }

        ans[t] = cur_ans;
        if (cur_state)
            ans[t] += cur_sz;
    }

    queries[node].clear();
    return;
}

int main(void)
{
    scanf("%d %d", &N, &Q);

    state.resize(N);
    par.resize(N);
    adj_list.resize(N);
    dp.resize(N);
    sz.resize(N);
    tmp_sz.resize(N);
    updates.resize(N);
    queries.resize(N);
    lazy.resize(N);

    ans.assign(Q, -1);

    for (int i = 0; i < N; i++)
        scanf("%d", &state[i]);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    initialize(0, -1);

    int BLOCK_SIZE = sqrt(N);
    int summed = 0;
    for (int t = 0; t < Q; t++) {
        int op, x;
        scanf("%d %d", &op, &x);
        x--;

        if (op == 1) {
            updates[x].push_back(mp(t, 0));
        }
        else {
            queries[x].push_back(t);
        }

        summed++;
        if (summed == BLOCK_SIZE) {
            process(0);
            updates[0].clear();
            summed = 0;
        }
    }

    if (summed)
        process(0);

    for (int i = 0; i < Q; i++) {
        if (ans[i] != -1)
            printf("%lld\n", ans[i]);
    }

    return 0;
}