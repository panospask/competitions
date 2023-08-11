#include "factories.h"
#include "vector"
#include "math.h"
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;

const ll INF = 1e18;

typedef pair<int, ll> pi;

int N;
vector<int> subtree_size;
vector<vector<pi>> adj_list;
vector<bool> removed;

// Ancestors in centroid tree(at most logN)
vector<vector<pi>> ancestors;
vector<ll> min_source_dist;

int calc_sb_size(int node, int par, ll d, int anc)
{
    subtree_size[node] = 1;

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh != par && !removed[neigh]) {
            subtree_size[node] += calc_sb_size(neigh, node, d + w, anc);
        }
    }

    if (anc != -1)
        ancestors[node].pb(mp(anc, d));

    return subtree_size[node];
}

int find_centroid(int node, int par, int sz)
{
    for (auto [neigh, w] : adj_list[node]) {
        if (!removed[neigh] && neigh != par && subtree_size[neigh] > sz / 2)
            return find_centroid(neigh, node, sz);
    }

    return node;
}

void centroid_decompose(int node)
{
    int c = find_centroid(node, -1, subtree_size[node]);

    removed[c] = true;

    for (auto [neigh, w] : adj_list[c]) {
        if (removed[neigh])
            continue;

        calc_sb_size(neigh, -1, w, c);
    }

    for (auto [neigh, w] : adj_list[c]) {
        if (removed[neigh])
            continue;

        centroid_decompose(neigh);
    }

    return;
}

void Init(int n, int A[], int B[], int D[])
{
    N = n;

    adj_list.resize(N);
    subtree_size.resize(N);
    min_source_dist.assign(N, INF);
    removed.resize(N);
    ancestors.resize(N);

    for (int i = 0; i < N - 1; i++) {
        adj_list[A[i]].pb(mp(B[i], D[i]));
        adj_list[B[i]].pb(mp(A[i], D[i]));
    }

    calc_sb_size(0, -1, 0, -1);
    centroid_decompose(0);
}

long long Query(int S, int X[], int T, int Y[])
{
    removed.assign(N, false);

    ll res = INF;

    for (int i = 0; i < S; i++) {
        int v = X[i];

        // Iterate over all ancestors of v
        min_source_dist[v] = 0;
        for (auto [u, d] : ancestors[v]) {
            min_source_dist[u] = min(min_source_dist[u], d);
        }
    }

    for (int i = 0; i < T; i++) {
        int v = Y[i];

        res = min(res, min_source_dist[v]);
        for (auto [u, d] : ancestors[v]) {
            res = min(res, d + min_source_dist[u]);
        }
    }

    for (int i = 0; i < S; i++) {
        int v = X[i];

        min_source_dist[v] = INF;
        for (auto [u, d] : ancestors[v])
            min_source_dist[u] = INF;
    }

    return res;
}
