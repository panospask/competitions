#include "garden.h"
#include "gardenlib.h"
#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

const int MAXUP = 30;

int N, Q;
vector<pi> queries;
vector<vector<int>> adj_list;

/*target[up][x]
 * x = 2 * i: The 2^up target of i if we reached i without going through the most beautiful path.
 * x = 2 * i + 1: The 2^up target of i if we reached i by going through the most beautiful path. 
 */
vector<int> target;

/*dist[i]:
 *Distance from i to the current destination (either 2 * P or 2 * P + 1)
 */
vector<int> dist;

// Variables used for cycle finding
vector<bool> on_stack;
vector<bool> visited;
int cur = 0, len = 0;

// Variables used for finding number of nodes that end at dest after some moves
vector<int> freq;
vector<int> freqmodlen;

// Final answer for each query
vector<int> ans;

// Returns distance from node to dest (2 * N if dest cannot be reached from node)
int dfs(int node, int dest)
{
    if (visited[node]) {
        if (on_stack[node]) {
            // New cycle
            // Check if destination is inside this new cycle
            // Since dfs started on dest, the completed cycle must also end on dest

            if (node == dest) {
                // dest belongs to this cycle
                len = cur;
                return 0;
            }
            else {
                // dest does not belong to a cycle
                return 2 * N;
            }
        }
        else {
            return dist[node];
        }
    }

    visited[node] = on_stack[node] = true;
    cur++;

    dist[node] = min(2 * N, dfs(target[node], dest) + 1);
    if (node == dest) {
        dist[node] = 0;
    }

    if (node % 2 == 0) {
        // We only care about even numbered nodes because they represent the starting positions
        freq[dist[node]]++;
    }

    on_stack[node] = false;
    cur--;

    return dist[node];
}

void process_destination(int t)
{
    visited.assign(2 * N, false);
    on_stack.assign(2 * N, false);
    dist.assign(2 * N + 1, 2 * N);
    len = cur = 0;
    freq.assign(2 * N + 1, 0);

    dfs(t, t);
    for (int i = 0; i < 2 * N; i++) {
        if (!visited[i]) {
            dfs(i, t);
        }
    }

    freqmodlen.assign(len, 0);

    int steps = 0;
    for (int i = 0; i < Q; i++) {
        while (steps < min(2 * N, queries[i].first)) {
            // Add new step
            if (len) {
                freqmodlen[steps % len] += freq[steps];
            }
            steps++;
        }

        if (queries[i].first < 2 * N) {
            ans[queries[i].second] += freq[queries[i].first];
        }
        if (len) {
            ans[queries[i].second] += freqmodlen[queries[i].first % len];
        }
    }
}

void add_target(int fr, int to)
{
    if (adj_list[to][0] == fr / 2) {
        target[fr] = 2 * to + 1;
    }
    else {
        target[fr] = 2 * to;
    }
}

void count_routes(int n, int M, int P, int R[][2], int q, int G[])
{
    N = n;
    Q = q;

    queries.resize(Q);
    ans.assign(Q, 0);
    adj_list.resize(N);
    target.resize(2 * N);

    for (int i = 0; i < Q; i++) {
        queries[i] = make_pair(G[i], i);
    }
    sort(queries.begin(), queries.end());

    for (int i = 0; i < M; i++) {
        adj_list[R[i][0]].pb(R[i][1]);
        adj_list[R[i][1]].pb(R[i][0]);
    }


    for (int i = 0; i < N; i++) {
        add_target(2 * i, adj_list[i][0]);

        if (adj_list[i].size() >= 2) {
            add_target(2 * i + 1, adj_list[i][1]);
        }
        else {
            add_target(2 * i + 1, adj_list[i][0]);
        }
    }

    process_destination(2 * P);
    process_destination(2 * P + 1);

    for (int i = 0; i < Q; i++) {
        answer(ans[i]);
    }
}


