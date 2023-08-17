#include "keys.h"
#include <vector>
#include <queue>
#include <set>
#include <stack>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

struct Node {
    int id;
    set<int> members;
    set<int> keys;

    set<pi> locked_edges;
    set<int> unlocked_edges;

    int size(void) {
        return members.size() + keys.size() + locked_edges.size() + unlocked_edges.size();
    }

    void clear(void) {
        members.clear();
        keys.clear();
        locked_edges.clear();
        unlocked_edges.clear();
    }
};

int N, M;
vector<vector<pi>> adj_list;

vector<Node> graph;

set<int> process;

vector<int> rep;
vector<int> nxt;
vector<int> heading;
vector<bool> vis;
vector<bool> in_cycle;
stack<int> cycle;

int find(int a)
{
    if (heading[a] != a)
        heading[a] = find(heading[a]);

    return heading[a];
}

// Assumes a.size() >= b.size()
// Merges b into a => b can be removed
void merge(Node& a, Node& b)
{
    for (auto m : b.members) {
        heading[m] = a.id;
        rep[m] = a.id;
        a.members.insert(m);
        a.unlocked_edges.erase(m);
    }

    for (auto v : b.unlocked_edges) {
        if (!a.members.count(v))
            a.unlocked_edges.insert(v);
    }

    for (auto [k, v] : b.locked_edges) {
        if (!a.keys.count(k))
            a.locked_edges.insert(mp(k, v));
        else
            a.unlocked_edges.insert(v);
    }

    for (auto k : b.keys) {
        a.keys.insert(k);

        while (true) {
            auto it = a.locked_edges.lower_bound(mp(k, 0));
            if (it == a.locked_edges.end() || (*it).first != k)
                break;

            a.unlocked_edges.insert((*it).second);
            a.locked_edges.erase(it);
        }
    }

    b.clear();
}

void dfs(int node)
{
    if (vis[node]) {
        if (in_cycle[node]) {
            heading[node] = node;
            process.insert(node);
            rep[node] = node;

            while (cycle.top() != node) {
                int v = cycle.top();
                cycle.pop();

                rep[v] = node;
                nxt[v] = node;
                merge(graph[node], graph[v]);
            }
        }

        return;
    }

    vis[node] = true;
    in_cycle[node] = true;
    cycle.push(node);

    int dest = *graph[node].unlocked_edges.begin();
    dfs(dest);

    in_cycle[node] = false;
    if (heading[node] == -1) {
        heading[node] = heading[dest];
        nxt[node] = dest;
        rep[node] = node;
    }
}

vector<int> find_reachable(vector<int> r, vector<int> u, vector<int> v, vector<int> c)
{
    N = r.size();
    M = u.size();

    adj_list.resize(N);
    graph.resize(N);
    heading.assign(N, -1);
    nxt.resize(N);
    rep.resize(N);
    vis.assign(N, false);
    in_cycle.assign(N, false);

    for (int i = 0; i < N; i++) {
        graph[i].id = i;
        graph[i].members.insert(i);
        graph[i].keys.insert(r[i]);
    }

    for (int i = 0; i < M; i++) {
        adj_list[u[i]].pb(mp(v[i], c[i]));
        adj_list[v[i]].pb(mp(u[i], c[i]));

        if (r[u[i]] == c[i]) {
            graph[u[i]].unlocked_edges.insert(v[i]);
        }
        else {
            graph[u[i]].locked_edges.insert(mp(c[i], v[i]));
        }

        if (r[v[i]] == c[i]) {
            graph[v[i]].unlocked_edges.insert(u[i]);
        }
        else {
            graph[v[i]].locked_edges.insert(mp(c[i], u[i]));
        }
    }

    vector<int> zero(N);
    bool found = false;
    for (int i = 0; i < N; i++) {
        zero[i] = graph[i].unlocked_edges.size() == 0;
        found = found || zero[i];
    }

    if (found) {
        return zero;
    }

    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            dfs(i);
            while (!cycle.empty())
                cycle.pop();
        }
    }

    while (!process.empty()) {

        int i = *process.begin();
        process.erase(i);

        // This is root :)
        while (!graph[i].unlocked_edges.empty()) {
            int v = *graph[i].unlocked_edges.begin();
            graph[i].unlocked_edges.erase(v);

            // Two options : v leads to i, or is independent
            if (find(v) == graph[i].id) {
                // Merge things
                v = rep[v];
                while (graph[i].members.count(v) == 0) {
                    merge(graph[i], graph[v]);
                    v = nxt[v];
                }

            }
            else {
                heading[i] = v;
                nxt[i] = v;
                break;
            }
        }
    }

    int min_v = __INT_MAX__;
    vector<int> min_nodes;
    for (int i = 0; i < N; i++) {
        if (find(i) == i) {
            // Root
            if (graph[i].members.size() < min_v) {
                min_v = graph[i].members.size();
                min_nodes.clear();
            }
            if (graph[i].members.size() == min_v) {
                for (auto j : graph[i].members)
                    min_nodes.pb(j);
            }
        }
    }

    vector<int> ans(N, 0);
    for (auto v : min_nodes)
        ans[v] = 1;

    return ans;
}