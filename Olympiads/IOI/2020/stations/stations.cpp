#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int MAXN = 1e3;

vector<vector<int>> adj_list;
vector<int> tin;
vector<int> dep;
vector<int> tout;
int counter = 0;

void euler(int node, int par)
{
    if (par == -1)
        dep[node] = 0;
    else
        dep[node] = dep[par] + 1;

    if (dep[node] % 2 == 0)
        tin[node] = counter++;

    for (auto neigh : adj_list[node])
        if (neigh != par)
            euler(neigh, node);

    if (dep[node] % 2 == 1)
        tout[node] = counter++;
}

bool tincmp(int a, int b)
{
    return a / MAXN < b / MAXN;
}

vector<int> label(int N, int K, vector<int> u, vector<int> v)
{
    adj_list.clear();
    dep.clear();
    tin.clear();
    tout.clear();

    adj_list.resize(N);
    tin.resize(N);
    dep.resize(N);
    tout.resize(N);
    counter = 0;

    for (int i = 0; i < N - 1; i++) {
        adj_list[u[i]].pb(v[i]);
        adj_list[v[i]].pb(u[i]);
    }

    euler(0, -1);

    vector<int> ans(N);

    for (int i = 0; i < N; i++) {

        if (dep[i] % 2)
            ans[i] = tout[i];
        else
            ans[i] = tin[i];
    }

    return ans;
}

bool inside(int a, int b, int c)
{
    return a <= b && c >= b;
}

int find_next_station(int s, int t, vector<int> c)
{
    if (c.size() == 1)
        return c.front();

    // Not at leaf
    // First figure out if this node saves tin or tout by looking at the parent(if it exists)

    // If it saves tin --> it would be smaller than all in c
    // If it saves tout --> it would be larger than all in c

    // It suffices to check the first and last element to find out
    int in, out;
    if (c.front() > s) {
        // It saves tin
        in = s;
        bool par = true;
        if (in == 0) {
            // No parent
            out = c.back();
            par = false;
        }
        else {
            // Exclude out of parent --> Out of the last child
            out = c[c.size() - 2];
        }

        if (!inside(in, t, out))
            return c.back();

        // Since the children save out, the first child that has tout[i] >= t is the ancestor
        int ans = lower_bound(c.begin(), c.end() - par, t) - c.begin();
        return c[ans];
    }
    else {
        assert(c.back() <= s);
        // It saves out
        bool par = true;
        out = s;
        in = c[1] - 1;

        if (!inside(in, t, out))
            return c.front();

        // Since the children save in, the last child that has tin[i] <= t is the ancestor
        int ans = upper_bound(c.begin() + par, c.end(), t) - c.begin() - 1;
        return c[ans];
    }
}