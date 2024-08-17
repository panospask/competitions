#include "game.h"
#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> rep;
vector<int> sz;
vector<vector<int>> queries;

int find(int a)
{
    if (rep[a] == a) {
        return a;
    }

    return rep[a] = find(rep[a]);
}

void unite(int a, int b)
{
    a = find(a);
    b = find(b);

    if (sz[a] < sz[b]) {
        swap(a, b);
    }

    rep[b] = a;
    sz[a] += sz[b];

    // Now for the queries part
    for (int i = 0; i < N; i++) {
        queries[a][i] += queries[b][i];
        queries[i][a] += queries[i][b];
    }
}

void initialize(int n)
{
    N = n;
    rep.resize(N);
    sz.resize(N);
    queries.assign(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        rep[i] = i;
        sz[i] = 1;
    }
}

int hasEdge(int u, int v)
{
    u = find(u);
    v = find(v);

    queries[u][v]++;
    queries[v][u]++;

    if (queries[u][v] == sz[u] * sz[v]) {
        unite(u, v);
        return 1;
    }
    
    return 0;
}