#include <bits/stdc++.h>
#include "islands.h"
#define mp make_pair
#define pb push_back
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;

typedef variant<bool, vector<int>> Result;
vector<int> ans;
vector<bool> vis;
vector<bool> in_cycle;
stack<int> cycle;
vector<bool> use;

int N, M;
vector<vector<pi>> adj_list;

Result sub1(void)
{
    if (adj_list[0].size() >= 2 && adj_list[1].size() >= 1) {
        ans.resize(6);
        ans[0] = adj_list[0][0].s;
        ans[1] = adj_list[1][0].s;
        ans[2] = adj_list[0][1].s;
        ans[3] = adj_list[0][0].s;
        ans[4] = adj_list[1][0].s;
        ans[5] = adj_list[0][1].s;

        return ans;
    }
    else {
        return false;
    }
}

// idx of canoo that travels from u to v
int get_idx(int u, int v, int mod)
{
    int pos = upper_bound(adj_list[u].begin(), adj_list[u].end(), mp(v, INT_MAX)) - adj_list[u].begin();
    return adj_list[u][pos - 1 - mod].s;
}

// Go t - u - t -v - t - u - t - v
void create_cycle(int t, int u, int v)
{
    int m = 0;
    if (u == v)
        m = 1;

    int t_u = get_idx(t, u, 0);
    int u_t = get_idx(u, t, 0);
    int t_v = get_idx(t, v, m);
    int v_t = get_idx(v, t, m);

    ans.pb(t_u);
    ans.pb(u_t);
    ans.pb(t_v);
    ans.pb(v_t);
    ans.pb(u_t);
    ans.pb(t_u);
    ans.pb(v_t);
    ans.pb(t_v);
}

Result sub2(void)
{
    create_cycle(0, 1, 2);

    return ans;
}

bool dfs3(int node, int par)
{
    if (adj_list[node].size() - (par != -1) >= 2) {
        int u = adj_list[node][0].f;
        int v = adj_list[node][1].f;
        if (u == par || v == par) {
            int t = adj_list[node][2].f;
            if (u == par)
                create_cycle(node, v, t);
            else
                create_cycle(node, u, t);
        }
        else
            create_cycle(node, u, v);

        return true;
    }

    for (auto neigh : adj_list[node]) {
        if (neigh.f == par)
            continue;

        ans.pb(neigh.s);
        if (dfs3(neigh.f, node)) {
            ans.pb(neigh.s);
            return true;
        }
        ans.pop_back();
    }

    return false;
}

Result sub3(void)
{
    if (dfs3(0, -1))
        return ans;
    else
        return false;
}

void gencycle(int ending)
{
    vector<int> cyc;
    use[ending] = true;
    ans.pop_back();
    while (cycle.top() != ending) {
        use[cycle.top()] = true;
        ans.pop_back();
        cyc.pb(cycle.top());
        cycle.pop();
    }
    cyc.pb(ending);
    reverse(cyc.begin(), cyc.end());

    vector<pi> to_nxt(cyc.size());
    for (int i = 0; i < cyc.size(); i++) {
        to_nxt[i] = mp(get_idx(cyc[i], cyc[i + 1], 0), get_idx(cyc[i], cyc[i + 1], 1));
    }
    to_nxt.back() = mp(get_idx(cyc.back(), cyc.front(), 0), get_idx(cyc.back(), cyc.front(), 1));

    for (int shift = 0; shift < cyc.size(); shift++) {
        int starting = (cyc.size() - shift) % cyc.size();
        for (int i = starting; i != starting + cyc.size(); i++) {
            int real = i % cyc.size();
            ans.pb(to_nxt[real].f);
        }
        for (int i = starting; i != starting + cyc.size(); i++) {
            int real = i % cyc.size();
            ans.pb(to_nxt[real].s);
        }
    }
}

bool dfs4(int node)
{
    if (vis[node]) {
        if (!in_cycle[node])
            return false;

        gencycle(node);
        return true;
    }

    vis[node] = true;
    in_cycle[node] = true;
    cycle.push(node);

    for (int i = 0; i < adj_list[node].size(); i += 2) {
        auto neigh = adj_list[node][i];

        ans.pb(neigh.s);
        if (dfs4(neigh.f)) {
            if (!use[node])
                ans.pb(neigh.s);
            return true;
        }
        ans.pop_back();
    }

    cycle.pop();
    in_cycle[node] = false;

    return false;
}

Result sub4(void)
{
    use.assign(N, false);
    vis.assign(N, false);
    in_cycle.assign(N, false);

    if (dfs4(0))
        return ans;
    else
        return false;
}

Result find_journey(int n, int m, vector<int> u, vector<int> v)
{
    N = n;
    M = m;

    adj_list.resize(N);

    bool is3 = !(M % 2), is4 = !(M % 2);
    for (int i = 0; i < M; i++) {
        adj_list[u[i]].pb(mp(v[i], i));

        if (i % 2) {
            is3 = is3 && u[i - 1] == v[i] && v[i - 1] == u[i];
            is4 = is4 && u[i - 1] == u[i] && v[i - 1] == v[i];
        }
    }
    for (int i = 0; i < N; i++)
        sort(adj_list[i].begin(), adj_list[i].end());

    bool is2 = false;
    if (N <= 400) {
        is2 = true;
        for (int i = 0; i < N; i++) {
            if (adj_list[i].size() != N - 1) {
                is2 = false;
            }
            else {
                set<int> seen;
                for (int j = 0; j < adj_list[i].size(); j++)
                    seen.insert(adj_list[i][j].f);

                is2 = is2 && seen.size() == N - 1;
            }
        }
    }

    if (n == 2)
        return sub1();
    if (is2)
        return sub2();
    if (is3)
        return sub3();
    if (is4)
        return sub4();

    return false;
}