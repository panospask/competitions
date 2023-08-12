#include "keys.h"
#include "vector"
#include "queue"

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int N, M;
vector<vector<pi>> adj_list;
vector<bool> vis;
vector<bool> have;
vector<vector<int>> at;
vector<int> key;

int bfs(int node)
{
    vis.assign(N, false);
    have.assign(N, false);
    at.assign(N, vector<int>(0));
    int res = 0;

    queue<int> q;
    q.push(node);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (vis[v])
            continue;

        vis[v] = true;
        res++;


        if (!have[key[v]]) {
            have[key[v]] = true;
            for (auto u : at[key[v]])
                if (!vis[u])
                    q.push(u);
        }

        for (auto [neigh, k] : adj_list[v]) {
            if (vis[neigh])
                continue;

            if (have[k])
                q.push(neigh);
            else
                at[k].push_back(neigh);
        }
    }

    return res;
}

vector<int> find_reachable(vector<int> r, vector<int> u, vector<int> v, vector<int> c)
{
    N = r.size();
    M = u.size();
    key = r;

    adj_list.resize(N);

    for (int i = 0; i < M; i++) {
        adj_list[u[i]].pb(mp(v[i], c[i]));
        adj_list[v[i]].pb(mp(u[i], c[i]));
    }


    int ans = __INT_MAX__;
    vector<int> vs;

    for (int i = 0; i < N; i++) {
        int cur = bfs(i);
        if (cur < ans) {
            ans = cur;
            vs.clear();
        }
        if (cur == ans)
            vs.pb(i);
    }

    vector<int> ret;
    ret.assign(N, 0);

    for (auto v : vs)
        ret[v] = 1;

    return ret;
}